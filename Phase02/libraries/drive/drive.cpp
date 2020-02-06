#include "Arduino.h"
#include "drive.h"

const static int MAX_SPEED = 240;
const static int speed2 = 175;

const static int left_speed = 3;
const static int right_speed = 9;
const static int left_direction = 24;
const static int right_direction = 22;

#define MOTOR_FORWARD 1
#define MOTOR_BACK 0

void Drive_forward() {
    analogWrite(left_speed, MAX_SPEED);
    analogWrite(right_speed, MAX_SPEED);
    digitalWrite(left_direction, MOTOR_FORWARD);
    digitalWrite(right_direction, MOTOR_FORWARD);
}

void Drive_backward() {
    analogWrite(left_speed, MAX_SPEED);
    analogWrite(right_speed, MAX_SPEED);
    digitalWrite(right_direction, MOTOR_BACK);
    digitalWrite(left_direction, MOTOR_BACK);
}

void Drive_stop() {
    analogWrite(left_speed, 0);
    analogWrite(right_speed, 0);
}

void Drive_spin_left() {
    analogWrite(left_speed, MAX_SPEED);
    analogWrite(right_speed, MAX_SPEED);
    digitalWrite(left_direction, MOTOR_BACK);
    digitalWrite(right_direction, MOTOR_FORWARD);
}

void Drive_spin_right() {
    analogWrite(left_speed, MAX_SPEED);
    analogWrite(right_speed, MAX_SPEED);
    digitalWrite(left_direction, MOTOR_FORWARD);
    digitalWrite(right_direction, MOTOR_BACK);
}

void Drive_pivot_left() {
    analogWrite(left_speed, 0);
    analogWrite(right_speed, MAX_SPEED);
    digitalWrite(left_direction, MOTOR_FORWARD);
    digitalWrite(right_direction, MOTOR_FORWARD);
}

void Drive_pivot_right() {
    analogWrite(left_speed, MAX_SPEED);
    analogWrite(right_speed, 0);
    digitalWrite(left_direction, MOTOR_FORWARD);
    digitalWrite(right_direction, MOTOR_FORWARD);
}