
const long BAUDRATE = 9600;   
unsigned long vorigeTijd = 0;
const unsigned long zendInterval = 3000; 
int teller = 0;

void setup() {
  Serial.begin(BAUDRATE);
  delay(1000);

  Serial.println("=== DRAADLOZE COMMUNICATIE TEST START ===");
  Serial.print("Baudrate: ");
  Serial.println(BAUDRATE);
  Serial.println("Wacht op berichten...");

}

void loop() {

  if (Serial.available() > 0) {
    String ontvangen = Serial.readStringUntil('\n');
    ontvangen.trim(); 

    if (ontvangen.length() > 0) {
      Serial.print("Ontvangen: ");
      Serial.println(ontvangen);

      
      if (ontvangen.equalsIgnoreCase("PING")) {
        Serial.println("PONG");
      }
    }
  }

  
  unsigned long huidigeTijd = millis();
  if (huidigeTijd - vorigeTijd >= zendInterval) {
    vorigeTijd = huidigeTijd;
    teller++;
    Serial.print("Testbericht #");
    Serial.println(teller);
  }
}