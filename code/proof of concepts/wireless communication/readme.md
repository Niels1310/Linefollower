# draadloze communicatie proof of concept
minimale hard- en software waarmee aangetoond wordt dat duplex kan gecommuniceerd worden tussen de microcontroller en een [laptop|smartphone] (schappen wat niet past), gebruik makend van [programma] (in te vullen)
<br />
### configuratie

### opmerkingen

### gebruiksaanwijzing



/*
  Draadloze communicatie test
  - Toont aan dat draadloos zenden en ontvangen werkt
  - Controleert dat communicatieparameters juist zijn
  Geschikt voor HC-05, HC-06, XBee, of andere seriële draadloze modules
*/

const long BAUDRATE = 9600;   // Baudrate moet overeenkomen met de zender/ontvanger
unsigned long vorigeTijd = 0;
const unsigned long zendInterval = 3000; // elke 3 seconden zenden
int teller = 0;

void setup() {
  Serial.begin(BAUDRATE);
  delay(1000);

  Serial.println("=== DRAADLOZE COMMUNICATIE TEST START ===");
  Serial.print("Baudrate: ");
  Serial.println(BAUDRATE);
  Serial.println("Wacht op berichten...");

  // Indien LED op pin 13 aanwezig is, gebruiken we die als activiteitindicator
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // 1️⃣ Ontvangen: als er data binnenkomt, lezen we het
  if (Serial.available() > 0) {
    String ontvangen = Serial.readStringUntil('\n');
    ontvangen.trim(); // verwijder witruimte en line endings

    if (ontvangen.length() > 0) {
      Serial.print("Ontvangen: ");
      Serial.println(ontvangen);

      // 2️⃣ Antwoord geven op een PING-bericht
      if (ontvangen.equalsIgnoreCase("PING")) {
        Serial.println("PONG");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }

  // 3️⃣ Zenden: stuur periodiek een testbericht
  unsigned long huidigeTijd = millis();
  if (huidigeTijd - vorigeTijd >= zendInterval) {
    vorigeTijd = huidigeTijd;
    teller++;
    Serial.print("Testbericht #");
    Serial.println(teller);
  }
}
