#include "sensor.h"
#include "drive.h"

int red_out = 22;
int blue_out = 26;
int yellow_out = 24;
int orange_out = 23;
// Track_color init_color;

bool backed = false;
bool detected = false;
bool to_stop = false;

void setup() {
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(23, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  Track_color color = detect_color();

  // digitalWrite(10, LOW);
  // digitalWrite(12, HIGH);

  // Serial.print(init_color);
  // Serial.print("    ");
  // Serial.println(color);

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

  // if (color == yellow_track || color == blue_track) {
  //   Serial.println("right");
  //   Drive_pivot_right();
  // } else {
  //   Serial.println("left");
  //   Drive_pivot_left();
  // }

  // if (!backed) Drive_backward();
  // if (!backed && color == yellow_track) {
  //   Drive_stop();
  //   delay(700);
  //   backed = true;
  // }

  // if (backed && !detected) {
  //   Drive_spin_left();
  // }
  // if (backed && color == blue_track) {
  //   Drive_stop();
  //   delay(700);
  //   detected = true;
  // }

  // if (detected && !to_stop) {
  //   Drive_spin_right();
  // }

  // if (color == red_track) {
  //   Drive_stop();
  //   to_stop = true;
  // }


  if (detect_magnet()) {
    digitalWrite(orange_out, HIGH);
  } else {
    digitalWrite(orange_out, LOW);
  }
}
