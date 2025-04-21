#ifndef DRIVING_H
#define DRIVING_H

#include <avr/io.h>
#include <stdbool.h>
#include "motor.h"

/// @brief Drive the robot in a specified direction
/// @param duration The duration to drive
/// @param forward True for forward, false for reverse
void drive(uint16_t duration, bool forward);

/// @brief Turn the robot in a specified direction
/// @param duration The duration to turn
/// @param clockwise True for clockwise, false for counter clockwise
void turn(uint16_t duration, bool clockwise);

#endif