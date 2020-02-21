/**
 * Sensor.h
 * 
 * Junior Design
 * Vitellary Industries 2020
 * 
 * Interface for sensor measurements
 */

const  int RED_PIN = 10;
const  int BLUE_PIN = 12;
const  int SENSOR_PIN = A0;

enum Track_color {red_track, blue_track, yellow_track, black_track};

Track_color detect_color();
