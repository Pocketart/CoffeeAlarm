#include <TM1637Display.h>
#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

#define CLK 8
#define DIO 9
TM1637Display display(CLK, DIO);

// TONES  ==========================================
// Start by defining the relationship between 
//       note, period, &  frequency. 
#define  B3     4050    // 246.94 Hz
#define  C4     3830    // 261 Hz 
#define  D4     3400    // 294 Hz 
#define  E4     3038    // 329 Hz 
#define  F4     2864    // 349 Hz 
#define  G4     2550    // 392 Hz 
#define  A4     2272    // 440 Hz 
#define  B4     2028    // 493 Hz 
#define  C5     1912    // 523 Hz 

#define  B5     1012    // 987.76 Hz 
#define  C6     956     // 1046.5 Hz
#define  D6     851     // 1174.66 Hz 
#define  E6     758     // 1318.51 Hz 
#define  F6     716     // 1396.91 Hz 
#define  G6     638     // 1567.98 Hz 
#define  A6     518     // 1760 Hz 
#define  B6     506     // 1975.53 Hz 
#define  C7     478     // 2093 Hz 
// Define a special note, 'R', to represent a rest
#define  R     0

const int buzzer = 46;
const int sensor1 = 10;
const int sensor2 = 11;
const int button1 = 14;
const int button2 = 15;
const int button3 = 16;
const int button4 = 17;

int buttonState = 0;
int pin10, pin11, pin14, pin15, pin16, t, a=1200, set=0;
double turn=0.0;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT); 
  pinMode(button2, INPUT); 
  pinMode(button3, INPUT); 
  pinMode(sensor1, INPUT) ;
  pinMode(sensor2, INPUT) ;
  pinMode(buzzer, OUTPUT);

  rtc.begin();
  display.setBrightness(0xA);
  display.setColon(true);

}

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note)
int melody[] = {  G4, C5, B4, A4, G4, G4, D4, E4, F4, E4, F4, E4, F4, E4, D4, C4, B3, C4, R, C4, D4, D4, C4, R};
//int melody1[] = {  G6, C7, B6, A6, G6, G6, D6, E6, F6, E6, F6, E6, F6, E6, D6, C6, B5, C6, R, C4, D4, D4, C4, R};
int beats[]  = { 64, 32, 32, 32, 32, 32, 16, 48, 32, 32, 16, 32, 32, 32, 16, 32, 32, 64, 256, 64, 16, 32, 64, 256}; 
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(buzzer,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(buzzer, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

void loop() {
  
  pin10 = digitalRead(sensor1), pin11 = digitalRead(sensor2), pin14 = digitalRead(button1), pin15 = digitalRead(button2), pin16 = digitalRead(button3);
  
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
      if (a == t){
        // Set up a counter to pull from melody[] and beats[]
        for (int i=0; i<MAX_COUNT; i++) {
          tone_ = melody[i];
          beat = beats[i];
      
          duration = beat * tempo; // Set up timing
      
          playTone(); 
          // A pause between notes...
          delayMicroseconds(pause);
        }
      }
    }
  }
  delay(250);
}
