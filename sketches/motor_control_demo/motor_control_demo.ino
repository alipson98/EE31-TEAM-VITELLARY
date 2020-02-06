#include "drive.h"


void setup() {
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  Drive_forward();
  delay(1000);
  Drive_stop();
  delay(500);
  Drive_backward();
  delay(1000);
  Drive_stop();
  delay(500);
  Drive_spin_left();
  delay(1000);
  Drive_stop();
  delay(500);
  Drive_spin_right();
  delay(1000);
  Drive_stop();
  delay(500);
  Drive_pivot_left();
  delay(700);
  Drive_stop();
  delay(500);
  Drive_pivot_right();
  delay(700);
  Drive_stop();
  delay(1000);
}
