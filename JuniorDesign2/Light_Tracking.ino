const int right_1 = 5;
const int right_2 = 6;
const int left_3 = 9;
const int left_4 = 10;
const int greenLED = 12;
bool lightTrack = false;

#include <drive.h>


void setup() {
  pinMode(right_1,OUTPUT);
  pinMode(right_2,OUTPUT);
  pinMode(left_3,OUTPUT);
  pinMode(left_4,OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode (A0, INPUT);
  //Serial.begin(9600);
}

void loop() {
  Follow_Light();
}

void Follow_Light() {
    if (analogRead(A0) < 775) {
      digitalWrite(greenLED, HIGH);
      lightTrack = true;
      while(lightTrack) {
        Drive_forward();
          if (analogRead(A0) >= 775) {
            for (int i = 0; i < 4; i++) {
              Drive_pivot_left();
              delay(500);
              Drive_stop();
              if (analogRead(A0) < 775) {
                break;
              }
              Drive_pivot_right();
              delay(1000);
              if (analogRead(A0) < 775) {
                break;
              }
              if (i == 3) {
                lightTrack = false;
              }
            }
          
        }
    }
    Drive_stop();
    digitalWrite(greenLED, LOW);
  }
  
}
