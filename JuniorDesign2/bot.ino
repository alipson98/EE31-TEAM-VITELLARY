#include "Arduino.h"

const static int right_F = 5;
const static int right_R = 6;
const static int left_F = 9;
const static int left_R = 10;

const static int inf_reciever = 4;

void setup(){
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
Serial.begin(9600);
}


void loop(){
    if (digitalRead(inf_reciever)) {
        Drive_pivot_right();
        readthepins();
    } else {
        Drive_pivot_left();
        readthepins();
    }
  
  
}

void readthepins(){
 Serial.println(digitalRead(5));
  Serial.println(digitalRead(6));
  Serial.println(digitalRead(9));
  Serial.println(digitalRead(10)); 
}

void Drive_forward() {
  digitalWrite(left_F, HIGH);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, HIGH);
  digitalWrite(right_R, LOW);
}

void Drive_backward() {
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, HIGH);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, HIGH);
}

void Drive_stop() {
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, LOW);
}

//spin = center of rotation is the center of the bot
void Drive_spin_left(){
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, HIGH);
  digitalWrite(right_F, HIGH);
  digitalWrite(right_R, LOW);
  
}

void Drive_spin_right(){
  digitalWrite(left_F, HIGH);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, HIGH);
}

//pivot = center of rotation is left or right wheel
void Drive_pivot_left(){
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, HIGH);
  digitalWrite(right_R, LOW);
}

void Drive_pivot_right(){
  digitalWrite(left_F, HIGH);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, LOW);
}