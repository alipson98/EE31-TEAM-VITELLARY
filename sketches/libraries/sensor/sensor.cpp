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

static int red_val, blue_val, both_val;

/**
 * bug fix:
 * there was an issue where the track color would be incorrect when the sensor
 * LEDs switched due to bad data storage
 * fix by only updating variables 
 */
static int prev = 0;

bool detect_magnet() {
    return (analogRead(A1) <= 10);
}


Track_color detect_color() {
    int op = (millis() % 60) / 20;
    if (op == 0) {
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(RED_PIN, HIGH);
        if (op == prev){
            red_val = 10 * analogRead(SENSOR_PIN);
        }
        prev = op;
    } else if (op == 1) {
        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(RED_PIN, HIGH);
        if (op == prev) {
            both_val = 10 * analogRead(SENSOR_PIN);
        }
        prev = op;
    } else {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        if (op == prev) {
            blue_val = 10 * analogRead(SENSOR_PIN);
        }
        prev = op;
    }
    // count++;

    // Serial.print("red led: ");
    // // delay(5);
    // Serial.println(red_val);
    // // delay(5);
    // Serial.print("blue led: ");
    // // delay(5);
    // Serial.println(blue_val);
    // // delay(5);
    // Serial.print("both: ");
    // // delay(5);
    // Serial.println(both_val);


    if (both_val <= 1600) return black_track;

    if ((float)red_val / (float)blue_val >= 1.3) {
        return red_track;
    } else if ((float)blue_val / (float)red_val >= 2.2) {
        return blue_track;
    } else {
        if (both_val > 1600) {
            return yellow_track;
        } else {
            return black_track;
        }
    }

}