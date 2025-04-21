#include <avr/io.h>
#include <util/delay.h>

#include "driving.h"

void wait_for_pf4_press(void) {
    // make PF4 an input and enable its internal pull up
    PORTF.DIRCLR = PIN4_bm;
    PORTF.PIN4CTRL |= PORT_PULLUPEN_bm;
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
}

int main(void) {
    init_motors();

    wait_for_pf4_press();  // Wait for user to press button on pin 6
    while (1) {
        // Add main loop code here if needed

    }
}
