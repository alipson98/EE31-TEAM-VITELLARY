#include "drive.h"

void setup(){
pinMode(4, INPUT); //line reader LED
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
}

void loop(){
  while(digitalRead(4)){
    Drive_forward();
  }
  else{
    Drive_spin_right();
    if(digitalRead(4)){
      break;
    }
  }
}
