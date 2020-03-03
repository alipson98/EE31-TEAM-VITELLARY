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


//TODO: these are duplicates from sensor.h
// int red_val, blue_val, both_val;
// int count = 0;
// enum Track_color {red_track, blue_track, yellow_track, black_track};
// const  int RED_PIN = 10;
// const  int BLUE_PIN = 12;
// const  int SENSOR_PIN = A0;

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


// Track_color detect_color() {
//     int op = (millis() % 6000);
//     //int red_led, blue_led, both;
//     // digitalWrite(RED_PIN, LOW);
//     if (op < 2000) {
//         digitalWrite(BLUE_PIN, LOW);
//         // delay(10);
//         // ambient = 10 * analogRead(SENSOR_PIN);
//         digitalWrite(RED_PIN, HIGH);
//         red_val = 10 * analogRead(SENSOR_PIN);
//     } else if (op > 4000) {
//         digitalWrite(BLUE_PIN, HIGH);
//         digitalWrite(RED_PIN, HIGH);
//         //delay(5);
//         both_val = 10 * analogRead(SENSOR_PIN);
//     } else {
//         digitalWrite(RED_PIN, LOW);
//         // delay(5);
//         digitalWrite(BLUE_PIN, HIGH);
//         blue_val = 10 * analogRead(SENSOR_PIN);
//     }
//     count++;

//     // Serial.print("red led: ");
//     // // delay(5);
//     // Serial.println(red_val);
//     // // delay(5);
//     // Serial.print("blue led: ");
//     // // delay(5);
//     // Serial.println(blue_val);
//     // // delay(5);
//     // Serial.print("both: ");
//     // // delay(5);
//     // Serial.println(both_val);


//     if (both_val <= 1200) return black_track;

//     if ((float)red_val / (float)blue_val >= 1.2) {
//         return red_track;
//     } else if ((float)blue_val / (float)red_val >= 2) {
//         return blue_track;
//     } else {
//         if (both_val > 1500) {
//             return yellow_track;
//         } else {
//             return black_track;
//         }
//     }

// }
