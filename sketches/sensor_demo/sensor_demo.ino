#include "sensor.h"
#include "drive.h"

int red_out = 22;
int blue_out = 26;
int yellow_out = 24;
Track_color init_color;

void setup() {
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(34, OUTPUT);
  init_color = detect_color();
  delay(500);
  Serial.begin(9600);
}


void loop() {
  Track_color color = detect_color();

  Serial.print(init_color);
  Serial.print("    ");
  Serial.println(color);

  // digitalWrite(blue_out, HIGH);
  //     digitalWrite(yellow_out, HIGH);
  //     digitalWrite(red_out, HIGH);

  switch (color) {
      case red_track:
      digitalWrite(red_out, HIGH);
      digitalWrite(yellow_out, LOW);
      digitalWrite(blue_out, LOW);
      break;


      case blue_track:
      digitalWrite(blue_out, HIGH);
      digitalWrite(yellow_out, LOW);
      digitalWrite(red_out, LOW);
      break;

      case yellow_track:
      digitalWrite(blue_out, LOW);
      digitalWrite(yellow_out, HIGH);
      digitalWrite(red_out, LOW);
      break;

      case black_track:
      digitalWrite(blue_out, LOW);
      digitalWrite(yellow_out, LOW);
      digitalWrite(red_out, LOW);
      break;
  }
  if (init_color == color) {
    Drive_forward();
  } else {
    Drive_stop();
  }
}
