int buzzerSwitch = 33;

void setup() {
  pinMode(buzzerSwitch, OUTPUT);
  digitalWrite(buzzerSwitch, LOW);
}

void loop() {
  digitalWrite(buzzerSwitch, HIGH);
  delay(100);
  digitalWrite(buzzerSwitch, LOW);
  delay(250);
}
