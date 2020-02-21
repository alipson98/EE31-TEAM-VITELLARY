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



Track_color detect_color() {
    int red_led, blue_led, both;
    // digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    // delay(10);
    // ambient = 10 * analogRead(SENSOR_PIN);
    digitalWrite(RED_PIN, HIGH);
    delay(10);
    red_led = 10 * analogRead(SENSOR_PIN);
    digitalWrite(BLUE_PIN, HIGH);
    delay(10);
    both = 10 * analogRead(SENSOR_PIN);
    digitalWrite(RED_PIN, LOW);
    delay(10);
    blue_led = 10 * analogRead(SENSOR_PIN);

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
    } else if ((float)blue_led / (float)red_led >= 2.5) {
        return blue_track;
    } else {
        if (both > 1500) {
            return yellow_track;
        } else {
            return black_track;
        }
    }

}