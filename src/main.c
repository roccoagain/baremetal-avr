#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "driving.h"

// right encoder on PA0
ISR(PORTA_PORT_vect) {
    if (PORTA.INTFLAGS & PIN0_bm) {
        right_enc++;
        PORTA.INTFLAGS = PIN0_bm;    // clear PA0's flag
    }
}

// left encoder on PC6
ISR(PORTC_PORT_vect) {
    if (PORTC.INTFLAGS & PIN6_bm) {
        left_enc++;
        PORTC.INTFLAGS = PIN6_bm; // clear PC6's flag
    }
}

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

    // PA0 → toggle on rising edges
    PORTA.DIRCLR   = PIN0_bm;  
    PORTA.PIN0CTRL = PORT_ISC_RISING_gc;  

    // PC6 → toggle on rising edges
    PORTC.DIRCLR   = PIN6_bm;  
    PORTC.PIN6CTRL = PORT_ISC_RISING_gc;  

    sei(); // enable global interrupts

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
        drive_counts(500, true);
    }
    return 0;
}
