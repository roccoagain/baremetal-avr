#ifndef DRIVING_H
#define DRIVING_H

#include <avr/io.h>
#include <stdbool.h>
#include "motor.h"

/// @brief Drive the robot in a specified direction
/// @param duration The duration to drive
/// @param forward True for forward, false for reverse
void drive_time(uint16_t duration, bool forward);

/// @brief Turn the robot in a specified direction
/// @param duration The duration to turn
/// @param clockwise True for clockwise, false for counter clockwise
void turn_time(uint16_t duration, bool clockwise);

/// @brief Drive the robot a specified distance
/// @param distance The distance to drive in feet
/// @param forward True for forward, false for reverse
void drive_distance(uint16_t distance, bool forward);

/// @brief Turn the robot a specified distance
/// @param distance The angle to turn in degrees
/// @param clockwise True for clockwise, false for counter clockwise
void turn_distance(uint16_t distance, bool clockwise);

#endif