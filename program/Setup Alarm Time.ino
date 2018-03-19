#include <TM1637Display.h>
#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

#define CLK 8
#define DIO 9
TM1637Display display(CLK, DIO);

const int button1 = 14;
const int button2 = 15;
const int button3 = 16;

int buttonState = 0;
int pin14, pin15, pin16, t, a=1200, set=0;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT); 
  pinMode(button2, INPUT); 
  pinMode(button3, INPUT); 

  rtc.begin();
  display.setBrightness(0xA);
  display.setColon(true);

}

void loop() {
  
  pin14 = digitalRead(button1), pin15 = digitalRead(button2), pin16 = digitalRead(button3);
  
  if(pin14 == HIGH){
    if(set == 1){
      set = 2;
    }
    else if(set == 2){
      set = 0;
    }
    else if(set == 0){
      set = 1;
    }
  }
  else if(pin14 == LOW){
    if(set == 1){
      if(pin15 == HIGH){
        a += 100;
        if(a >= 2500){
          a -= 2400;
        }
        //display.showNumberDec(a, true);
      }
      else if(pin16 == HIGH){
        a -= 100;
        if(a < 100){
          a += 2400;
        }
        //display.showNumberDec(a, true);
      }
      display.showNumberDec(a, true);    
    }
    else if(set == 2){
      if(pin15 == HIGH){
        a += 1;
        if((a%100) >= 60){
          a += 40;
        }
        //display.showNumberDec(a, true);
      }
      else if(pin16 == HIGH){
        a -= 1;
        if((a%100) >= 60){
          a -= 40;
        }
        //display.showNumberDec(a, true);
      }
      display.showNumberDec(a, true);
    }
    else if(set == 0){
      DateTime now = rtc.now();
      t = now.hour() * 100 + now.minute();
      display.showNumberDec(t, true);
    }
  }
//  Serial.print(pin14);
//  Serial.print(pin15);
//  Serial.println(pin16);
  delay(250);
}
