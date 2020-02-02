/*
 * drive.h
 * 
 * code for controlling drive functions for the bot
 */

#ifndef DRIVE_H
#define DRIVE_H

class Drive
{
    public:
    // Drive();
    void forward();
    void backward();
    void turn_left();
    void turn_right();
    void pivot_left();
    void pivot_right();
    void stop();

    private:
    int left_speed = 10;
    int right_speed = 11;
    int left_direction = 22;
    int right_direction = 23;
};

#endif