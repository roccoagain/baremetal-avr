#include <avr/io.h>
#include <util/delay.h>

#include "driving.h"

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

int main(void) {
    PORTE.DIRSET = PIN2_bm;
    PORTE.OUTCLR = PIN2_bm; // start with LED off

    PORTF.DIRCLR = PIN4_bm;
    PORTF.PIN4CTRL |= PORT_PULLUPEN_bm;

    init_motors();

    while (1) {
        wait_for_pf4_press();  // Wait for user to press button on pin 6
        drive_time(500, true);
    }
}
