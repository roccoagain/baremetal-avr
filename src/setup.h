#ifndef SETUP_H 
#define SETUP_H

#include <avr/io.h>
#include <util/delay.h>

void setup_pwm() {
    PORTB.DIRSET = PIN0_bm | PIN1_bm;
    TCA0.SINGLE.CTRLD = TCA_SPLIT_SPLITM_bm;
    TCA0.SPLIT.CTRLB = TCA_SPLIT_LCMP0EN_bm | TCA_SPLIT_HCMP1EN_bm;
    TCA0.SPLIT.LPER = 255;
    TCA0.SPLIT.HPER = 255;
    TCA0.SPLIT.LCMP0 = 3 * 51;  // PWM level for PB0 / pin 9
    TCA0.SPLIT.HCMP1 = 3 * 51;  // PWM level for PB1 / pin 10
    TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV64_gc | TCA_SPLIT_ENABLE_bm;
}

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

#endif