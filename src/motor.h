#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>


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
    /// @brief PWM register
    volatile uint8_t* pwm_reg;
} Motor;

#endif