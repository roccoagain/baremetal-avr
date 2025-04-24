#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>

#include "driving.h"

/// @brief Function that halts until PF4 is pulled down
/// @param None
void wait_for_pf4_press(void) {
    // turn off LED
    PORTE.OUTCLR = PIN2_bm;
    // wait until PF4 reads LOW 
    while (PORTF.IN & PIN4_bm) {
        _delay_ms(10);
    }
    // debounce
    _delay_ms(50);
    // wait until PF4 HIGH again
    while (!(PORTF.IN & PIN4_bm)) {
        _delay_ms(10);
    }
    // turn on LED
    PORTE.OUTSET = PIN2_bm;
}

/// @brief Everything that needs to happen before the main loop
/// @param None
void setup(void) {
    // set up clock, this fixed my delay inaccuracies
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSC20M_gc);
    // set the prescaler to 1 so we get 20MHz
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, 0);
    // set up the LED on PE2, start with it off
    PORTE.DIRSET = PIN2_bm;
    PORTE.OUTCLR = PIN2_bm; 
    // set up the button on PF4
    PORTF.DIRCLR = PIN4_bm;
    PORTF.PIN4CTRL |= PORT_PULLUPEN_bm;
    // start pwm on PB0 and PB1
    init_motors();
}

/// @brief Calls setup, then enters main loop
/// @param None
/// @return 0 on success
int main(void) {
    setup();
    while (1) {
        // wait for PF4 to be pressed
        wait_for_pf4_press();

        // main routine

        // start and stop left motor
        drive_motor(&left_motors, true);
        _delay_ms(2000);
        stop_motor(&left_motors);
        _delay_ms(2000);

        // start and stop right motor
        drive_motor(&right_motors, true);
        _delay_ms(2000);
        stop_motor(&right_motors);
        _delay_ms(2000);
    }
    return 0;
}
