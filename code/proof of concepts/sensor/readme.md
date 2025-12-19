# Sensoren proof of concept

minimale hard- en software die aantoont dat minimaal 6 sensoren onafhankelijk van elkaar kunnen uitgelezen worden (geen calibratie, normalisatie of interpolatie). Hierbij moet een zo groot mogelijk bereik van de AD converter benut worden (indien van toepassing)

    #include "SerialCommand.h"
    #include "EEPROMAnything.h"
    
    #define SerialPort Serial
    #define Baudrate 115200
    #define MotorLeftForward 18
    #define MotorLeftBackward 19
    #define MotorRightForward 21
    #define MotorRightBackward 22
    #define PWMA 17
    #define PWMB 23
    #define ledSensor 12
    
    SerialCommand sCmd(SerialPort);
    bool debug;
    bool run;
    float iTerm = 0;
    float lastErr;
    unsigned long previous, calculationTime;
    
    const int sensor[] = {36, 39, 34, 35, 32, 33};
    
    
    struct param_t
    {
      unsigned long cycleTime;
      /* andere parameters die in het eeprom geheugen moeten opgeslagen worden voeg je hier toe ... */
      int black[6];
      int white[6];
      int power;
      float diff;
      float kp;
      float ki;
      float kd;
    } params;
    
    void setup() {
      SerialPort.begin(Baudrate);
      EEPROM.begin(512);
      sCmd.addCommand("set", onSet);
      sCmd.addCommand("debug", onDebug);
      sCmd.addCommand("run", onRun);
      sCmd.addCommand("calibrate", onCalibrate);
      sCmd.setDefaultHandler(onUnknownCommand);
      EEPROM_readAnything(0, params);
       SerialPort.println("ready"); 
    
      // Defined in thingProperties.h
      initProperties();
    
      // Connect to Arduino IoT Cloud
      ArduinoCloud.begin(ArduinoIoTPreferredConnection);
      
      /*
         The following function allows you to obtain more information
         related to the state of network and IoT Cloud connection and errors
         the higher number the more granular information you’ll get.
         The default is 0 (only errors).
         Maximum is 4
     */
      setDebugMessageLevel(2);
      ArduinoCloud.printDebugInfo();
    }
    void loop() {
     for (int i = 0; i<6; i++)
       {
         Serial.print(analogRead(sensor[i]));
         Serial.print(" ");
       }
       Serial.println();
    }
