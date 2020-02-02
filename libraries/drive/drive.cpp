#include "Arduino.h"
#include "drive.h"

// Drive::Drive() {
    
// }

void Drive::forward() {
    analogWrite(left_speed, 255);
    analogWrite(right_speed, 255);
    digitalWrite(left_direction, 1);
    digitalWrite(right_direction, 1);
}

void Drive::backward() {
    analogWrite(left_speed, 255);
    analogWrite(right_speed, 255);
    digitalWrite(right_direction, 0);
    digitalWrite(left_direction, 0);
}

void Drive::stop() {
    analogWrite(left_speed, 0);
    analogWrite(right_speed, 0);
}