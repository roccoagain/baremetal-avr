#include <avr/io.h>
#include <util/delay.h>

typedef struct {
    // forward port and pin
    volatile uint8_t* fwd_port;
    uint8_t fwd_pin;
    // backward port and pin
    volatile uint8_t* rev_port;
    uint8_t rev_pin;
    // pwm register
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


int main(void) {
    setup_pwm();

    wait_for_button_press();  // Wait for user to press button on pin 6
    while (1) {
        // Add main loop code here if needed

    }
}
