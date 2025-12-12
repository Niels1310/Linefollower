#include "SerialCommand.h"
#include "EEPROMAnything.h"

#define SerialPort Serial
#define Baudrate 115200

SerialCommand sCmd(SerialPort);

unsigned long previous, calculationTime;
unsigned long blinkTimer = 0;
bool ledState = false;
bool run = true; // LED actief

// Magic number om EEPROM geldigheid te detecteren
#define EEPROM_SIGNATURE 0xBEEFCAFE

// Struct met parameters + handtekening
struct param_t
{
  unsigned long signature;       // herkenningswaarde
  unsigned long cycleTime;       // in microseconden
  unsigned long knipperPeriode;  // in milliseconden
} params;

// Functieprototypes
void onSet();
void onDebug();
void onUnknownCommand(char *command);
void start();
void stop();
void blinkSequenceSetup();

void setup()
{
  SerialPort.begin(Baudrate);

  // Commands
  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("start", start);
  sCmd.addCommand("stop", stop);
  sCmd.setDefaultHandler(onUnknownCommand);

  // Lees parameters uit EEPROM
  EEPROM_readAnything(0, params);

  // Controleer of EEPROM geldig is
  if (params.signature != EEPROM_SIGNATURE)
  {
    SerialPort.println("EEPROM leeg of ongeldig — initialiseer standaardwaarden");
    params.signature = EEPROM_SIGNATURE;
    params.cycleTime = 50000;       // 50 ms
    params.knipperPeriode = 1000;   // 1 s
    EEPROM_writeAnything(0, params);
  }

  pinMode(LED_BUILTIN, OUTPUT);
  blinkSequenceSetup();

  SerialPort.println("ready");
}

void loop()
{
  sCmd.readSerial();

  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;

    if (run)
    {
      blinkTimer += params.cycleTime / 1000; // µs → ms
      if (blinkTimer >= (params.knipperPeriode / 2))
      {
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
        blinkTimer = 0;
      }
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}

// ===== Commando’s =====

void onSet()
{
  char* param = sCmd.next();
  char* value = sCmd.next();

  if (!param || !value) return;

  if (strcmp(param, "cycle") == 0)
  {
    params.cycleTime = atol(value);
  }
  else if (strcmp(param, "blink") == 0)
  {
    params.knipperPeriode = atol(value);
  }
  else
  {
    SerialPort.println("onbekende parameter");
    return;
  }

  // Bewaar in EEPROM
  EEPROM_writeAnything(0, params);
  SerialPort.println("parameter opgeslagen");
}

void onDebug()
{
  SerialPort.print("cycle time (us): ");
  SerialPort.println(params.cycleTime);
  SerialPort.print("blink periode (ms): ");
  SerialPort.println(params.knipperPeriode);
  SerialPort.print("run: ");
  SerialPort.println(run ? "true" : "false");
  SerialPort.print("calculation time (us): ");
  SerialPort.println(calculationTime);
  calculationTime = 0;
}

void onUnknownCommand(char *command)
{
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void start()
{
  run = true;
  SerialPort.println("knipperlicht gestart");
}

void stop()
{
  run = false;
  digitalWrite(LED_BUILTIN, LOW);
  SerialPort.println("knipperlicht gestopt");
}

// ===== Opstartsequentie =====
void blinkSequenceSetup()
{
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
  }
  delay(500);
}
