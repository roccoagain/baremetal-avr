#include <avr/io.h>

#include "motor.h"
#include "setup.h"

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



int main(void) {
    setup_pwm();

    wait_for_pf4_press();  // Wait for user to press button on pin 6
    while (1) {
        // Add main loop code here if needed

    }
}
