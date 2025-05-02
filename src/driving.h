#ifndef DRIVING_H
#define DRIVING_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "motor.h"


#define AFTER_MOVE_DELAY 200 // 100ms delay after moving
#define TICKS_PER_FOOT 1250  // 1250 ticks for 1 foot
#define TICKS_PER_DEGREE (3000.0 / 360.0) // 3000 ticks for a full rotation

/// @brief Drive the robot in a specified direction
/// @param duration The duration to drive (ms)
/// @param forward True for forward, false for reverse
void drive_time(uint16_t duration, bool forward);

/// @brief Turn the robot in a specified direction
/// @param duration The duration to turn (ms)
/// @param clockwise True for clockwise, false for counter clockwise
void turn_time(uint16_t duration, bool clockwise);

/// @brief Drive the robot for a specified number of encoder counts
/// @param enc_count The count to drive until
/// @param forward True for forward, false for reverse
void drive_counts(uint16_t enc_count, bool forward);

/// @brief Turn the robot for a specified number of encoder counts
/// @param enc_count The count to turn until
/// @param forward True for clockwise, false for counter clockwise
void turn_counts(uint16_t enc_count, bool clockwise);

/// @brief Drive the robot a specified distance
/// @param distance The distance to drive in feet
/// @param forward True for forward, false for reverse
void drive_distance(uint16_t feet, bool forward);

/// @brief Turn the robot a specified degrees
/// @param distance The angle to turn in degrees
/// @param clockwise True for clockwise, false for counter clockwise
void turn_degrees(uint16_t degrees, bool clockwise);

#endif