int buzzerPin= 9;


void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  tone(buzzerPin, 700);
  delay(1500);
  noTone(buzzerPin);
  delay(3000);
 
}
