/**
 * Sensor.h
 * 
 * Junior Design
 * Vitellary Industries 2020
 * 
 * Interface for sensor measurements
 */


#include "Arduino.h"
#include "sensor.h"

static int red_led = 0, blue_led = 0, both = 0; 
const  int timing_interval = 50;

int detect_magnet() {
    // Serial.println(analogRead(A1));
    return analogRead(A1);
}


Track_color detect_color() {
    // Serial.println("entering");
    int red_led, blue_led, both;
    // digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    // delay(2);
    // ambient = 10 * analogRead(SENSOR_PIN);
    digitalWrite(RED_PIN, HIGH);
    delay(2);
    red_led = 10 * analogRead(SENSOR_PIN);
    digitalWrite(BLUE_PIN, HIGH);
    delay(2);
    both = 10 * analogRead(SENSOR_PIN);
    digitalWrite(RED_PIN, LOW);
    delay(2);
    blue_led = 10 * analogRead(SENSOR_PIN);
    digitalWrite(BLUE_PIN, LOW);


    // int curr_time = millis() % timing_interval;

    // if (curr_time < timing_interval/3) {
    //     // Serial.println("red");
    //     digitalWrite(BLUE_PIN, LOW);
    //     digitalWrite(RED_PIN, HIGH);
    //     red_led = 10 * analogRead(SENSOR_PIN);
    // } else if (curr_time < 2 * timing_interval / 3) {
    //     // Serial.println("both");
    //     digitalWrite(BLUE_PIN, HIGH);
    //     digitalWrite(RED_PIN, HIGH);
    //     both = 10 * analogRead(SENSOR_PIN);
    // } else {
    //     // Serial.println("blue");
    //     digitalWrite(BLUE_PIN, HIGH);
    //     digitalWrite(RED_PIN, LOW);
    //     blue_led = 10 * analogRead(SENSOR_PIN);
    // }

    // Serial.begin(9600);
    // Serial.print("red led: ");
    // delay(5);
    // Serial.println(red_led);
    // delay(5);
    // Serial.print("blue led: ");
    // delay(5);
    // Serial.println(blue_led);
    // delay(5);
    // Serial.print("both: ");
    // delay(5);
    // Serial.println(both);


    if (both <= 1200) return black_track;

    if ((float)red_led / (float)blue_led >= 1.3) {
        return red_track;
    } else if ((float)blue_led / (float)red_led >= 2.2) {
        return blue_track;
    } else {
        if (both > 1500) {
            return yellow_track;
        } else {
            return black_track;
        }
    }

}