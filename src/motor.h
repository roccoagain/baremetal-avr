#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>
#include <stdbool.h>

/// @brief Motor configuration struct
typedef struct {
    /// @brief Port register for forward direction pin
    volatile uint8_t* fwd_port;
    /// @brief Pin number for forward direction
    uint8_t fwd_pin;
    /// @brief Port register for reverse direction pin
    volatile uint8_t* rev_port;
    /// @brief Pin number for reverse direction
    uint8_t rev_pin;
} Motor;

/// @brief Left motor configuration
extern Motor left_motors;
/// @brief Right motor configuration
extern Motor right_motors;

/// @brief Set up everything needed for the motors; PWM and output pins
/// @param None
void init_motors(void);

/// @brief Sets both direction pins to LOW, stopping the motor
/// @param motor The motor to stop
void stop_motor(Motor* motor);

/// @brief Sets a direction pin HIGH to drive the motor in that direction
/// @param motor The motor to drive
/// @param forward True for forward, false for reverse
void drive_motor(Motor* motor, bool forward);

#endif