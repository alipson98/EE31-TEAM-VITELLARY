#include "drive.h"

void setup(){
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
Serial.begin(9600);
}


void loop(){
  Drive_forward();
  readthepins();
  delay(5000);
  
  Drive_stop();
  readthepins();
  delay(5000);
  
  Drive_backward();
  readthepins();
  delay(3000);
  
  Drive_stop();
  readthepins();
  delay(3000);
  
  Drive_pivot_left();
  readthepins();
  delay(3000);

  Drive_stop();
  readthepins();
  delay(3000);
  
  Drive_pivot_right();
  readthepins();
  delay(3000);

  Drive_stop();
  readthepins();
  delay(3000);
  
  Drive_spin_left();
  readthepins();
  delay(3000);

  Drive_stop();
  readthepins();
  delay(3000);
  
  Drive_spin_right();
  readthepins();
  delay(3000);

  Drive_stop();
  readthepins();
  delay(3000);
  
  
}

void readthepins(){
 Serial.println(digitalRead(5));
  Serial.println(digitalRead(6));
  Serial.println(digitalRead(9));
  Serial.println(digitalRead(10)); 
}
