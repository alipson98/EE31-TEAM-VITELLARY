#include "Arduino.h"

const static int right_F = 5;
const static int right_R = 6;
const static int left_F = 9;
const static int left_R = 10;
const int greenLED = 12;
bool lightTrack = false;

const static int inf_reciever = 4;

const int AN_SPEED = 100;
const int LIGHT_THRESHOLD = 775;

void setup(){
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(A0, INPUT);
    Serial.begin(9600);
}


void loop(){
    // if (digitalRead(inf_reciever)) {
    //     Drive_pivot_right();
    // } else {
    //     Drive_pivot_left();
    // }
    Follow_Light();
}

void readthepins(){
 Serial.println(digitalRead(5));
  Serial.println(digitalRead(6));
  Serial.println(digitalRead(9));
  Serial.println(digitalRead(10)); 
}

void Drive_forward() {
  analogWrite(left_F, AN_SPEED);
  analogWrite(left_R, 0);
  analogWrite(right_F, AN_SPEED);
  analogWrite(right_R, 0);
}

void Drive_backward() {
  analogWrite(left_F, 0);
  analogWrite(left_R, AN_SPEED);
  analogWrite(right_F, 0);
  analogWrite(right_R, AN_SPEED);
}

void Drive_stop() {
  analogWrite(left_F, 0);
  analogWrite(left_R, 0);
  analogWrite(right_F, 0);
  analogWrite(right_R, 0);
}

//spin = center of rotation is the center of the bot
void Drive_spin_left(){
  analogWrite(left_F, 0);
  analogWrite(left_R, AN_SPEED);
  analogWrite(right_F, AN_SPEED);
  analogWrite(right_R, 0);
  
}

void Drive_spin_right(){
  analogWrite(left_F, AN_SPEED);
  analogWrite(left_R, 0);
  analogWrite(right_F, 0);
  analogWrite(right_R, AN_SPEED);
}

//pivot = center of rotation is left or right wheel
void Drive_pivot_left(){
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, LOW);
  analogWrite(right_F, AN_SPEED);
  digitalWrite(right_R, LOW);
}

void Drive_pivot_right(){
  analogWrite(left_F, AN_SPEED);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, LOW);
}

void Follow_Light() {
    if (analogRead(A0) < LIGHT_THRESHOLD) {
      digitalWrite(greenLED, HIGH);
      lightTrack = true;
      while(lightTrack) {
        Drive_forward();
          if (analogRead(A0) >= LIGHT_THRESHOLD) {
            for (int i = 0; i < 4; i++) {
              Drive_pivot_left();
              delay(500);
              Drive_stop();
              if (analogRead(A0) < LIGHT_THRESHOLD) {
                break;
              }
              Drive_pivot_right();
              delay(1000);
              if (analogRead(A0) < LIGHT_THRESHOLD) {
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