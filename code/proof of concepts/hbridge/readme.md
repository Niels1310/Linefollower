# H-Bridge proof of concept

minimale hard- & software + stappenplan dat aantoont dat 2 motoren onafhankelijk van elkaar kunnen draaien, en (traploos) regelbaar zijn in snelheid en draairichting.

    #define MotorLeftForward 18
    #define MotorLeftBackward 19
    #define MotorRightForward 21
    #define MotorRightBackward 22
    #define PWMA 17
    #define PWMB 23
    #define ledSensor 12
    
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
    
    pinMode(MotorLeftForward, OUTPUT);
      pinMode(MotorLeftBackward, OUTPUT);
      pinMode(MotorRightForward, OUTPUT);
      pinMode(MotorRightBackward, OUTPUT);
      pinMode(PWMA, OUTPUT);
      pinMode(PWMB, OUTPUT);
      pinMode(ledSensor, OUTPUT);
    
    
      digitalWrite(PWMA, HIGH);
      digitalWrite(PWMB, HIGH);
    
        power = params.power;
          diff = params.diff;
          kp = params.kp;
        }
    
        void loop() {
        if (run && (current - previous >= params.cycleTime)) {
        previous = current;
        
        int powerLeft = 0;
        int powerRight = 0;
    
        if (output >= 0) {
          powerLeft = constrain(params.power + params.diff * output, -255, 255);
          powerRight = constrain(powerLeft - output, -255, 255);
          powerLeft = powerRight + output;
        } else {
          powerRight = constrain(params.power - params.diff * output, -255, 255);
          powerLeft = constrain(powerRight + output, -255, 255);
          powerRight = powerLeft - output;
        }
    
        analogWrite(MotorRightForward, powerLeft > 0 ? powerLeft : 0);
        analogWrite(MotorRightBackward, powerLeft < 0 ? -powerLeft : 0);
        analogWrite(MotorLeftForward, powerRight > 0 ? powerRight : 0);
        analogWrite(MotorLeftBackward, powerRight < 0 ? -powerRight : 0);
      }
    
    void onSet()
    {
      char *param = sCmd.next();
      char *value = sCmd.next();
    
      if (strcmp(param, "cycle") == 0)
      {
        long newCycleTime = atol(value);
        float ratio = ((float) newCycleTime) / ((float) params.cycleTime);
        params.ki *= ratio;
        params.kd /= ratio;
        params.cycleTime = newCycleTime;
      }
      else if (strcmp(param, "power") == 0) params.power = atol(value); // de snelheid waarmee de robot rijd!
      else if (strcmp(param, "diff") == 0) params.diff = atof(value); // trager of sneller rijden als de fout groot of klein is! tussen 0 en 1! (voor in de bochten)!
      else if (strcmp(param, "kp") == 0) params.kp = atof(value); // de grootte waarmee de roobot zijn fout corrigeerd!
      else if (strcmp(param, "ki") == 0)
      {
        float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
        params.ki = atof(value) * cycleTimeInSec;
      }
      else if (strcmp(param, "kd") == 0)
      {
        float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
        params.kd = atof(value) / cycleTimeInSec;
      }
    
      /* parameters een nieuwe waarde geven via het set commando doe je hier ... */
      EEPROM_writeAnything(0, params);
      EEPROM.commit();
    }
    
    void onRun() {
      run = true;
      iTerm = 0;
      SerialPort.println("RUN command ontvangen");
    }
    
    void stopMotors() {
      analogWrite(MotorLeftForward, 0);
      analogWrite(MotorLeftBackward, 0);
      analogWrite(MotorRightForward, 0);
      analogWrite(MotorRightBackward, 0);
    }
