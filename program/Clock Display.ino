
//#include <DS3231.h>
#include <TM1637Display.h>
#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

#define CLK 8
#define DIO 9
//DS3231 rtc(SDA, SCL);
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(115200);
  rtc.begin();

  display.setBrightness(0xA);
  display.setColon(true);
}

void loop() {
  DateTime now = rtc.now();

  int t = now.hour() * 100 + now.minute();
  display.showNumberDec(t, true);
  
  delay(1500); 
}
