int buzzerPin= 9;


void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  tone(buzzerPin, 300, 1000); // (pinNum, frequency, duration_milisec)
  // tone duration is independent from program. runs on internal clock
  delay(1500);
  noTone(buzzerPin);
  delay(3000);
 
}
