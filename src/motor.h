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

Motor left_motor = {
    .fwd_port = &PORTE.OUT,
    .fwd_pin = PIN0_bm,
    .rev_port = &PORTE.OUT,
    .rev_pin = PIN1_bm,
    .pwm_reg = &TCA0.SPLIT.LCMP0, // LCMP0 drives WO0 (PB0)
};

Motor right_motor = {
    .fwd_port = &PORTA.OUT,
    .fwd_pin = PIN1_bm,
    .rev_port = &PORTE.OUT,
    .rev_pin = PIN3_bm,
    .pwm_reg = &TCA0.SPLIT.HCMP1, // HCMP1 drives WO1 (PB1)
};

#endif