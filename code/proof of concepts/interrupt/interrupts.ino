
const byte KNOP_PIN = 10;            
const byte LED_PIN = 2;              
volatile bool robotActief = false;   
volatile unsigned long laatsteInterruptTijd = 0; 
const unsigned long DEBOUNCE_TIJD = 200; 

void setup() {
  pinMode(KNOP_PIN, INPUT_PULLUP); 
  pinMode(LED_PIN, OUTPUT);
  
  
  attachInterrupt(digitalPinToInterrupt(KNOP_PIN), knopInterrupt, FALLING);

  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
  Serial.println("Robot klaar. Druk op de knop om te starten/stoppen.");
}

void loop() {
  
  if (robotActief) {
    digitalWrite(LED_PIN, HIGH);
    
  } else {
    digitalWrite(LED_PIN, LOW);
    
  }

  
  delay(50);
}


void knopInterrupt() {
  unsigned long huidigeTijd = millis();
  
  
  if (huidigeTijd - laatsteInterruptTijd > DEBOUNCE_TIJD) {
    robotActief = !robotActief;
    laatsteInterruptTijd = huidigeTijd;
  }
}