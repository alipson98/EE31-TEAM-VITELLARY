// #include "drive.h"

const int ANALOG_READ_MAX = 1023;
int driveSpeed1 = 255;
int driveSpeed2 = 255;
int motor1 = 9;
int motor2 = 10;
int pot1 = A0;
int pot2 = A1;

// Drive drive;


void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(26, OUTPUT);

  Serial.begin(9600);
  while (! Serial);
  Serial.println("Serial ready.");
}

void loop() {
  // drive.forward();
  // delay(5000);
  // drive.backward();
  // drive.stop();
  delay(1000);
}
