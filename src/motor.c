#include "motor.h"

volatile uint16_t right_enc = 0;
volatile uint16_t left_enc = 0;

Motor left_motor = {
    // PE0 is forward
    .fwd_port = &PORTE.OUT,
    .fwd_pin = PIN0_bm,
    // PE1 is reverse
    .rev_port = &PORTE.OUT,
    .rev_pin = PIN1_bm,
    // note: left motors are driven by TCA0_SPLIT.LCMP0 on PB0
};

Motor right_motor = {
    // PA1 is forward
    .fwd_port = &PORTA.OUT,
    .fwd_pin = PIN1_bm,
    // PE3 is reverse
    .rev_port = &PORTE.OUT,
    .rev_pin = PIN3_bm,
    // note: right motors are driven by TCA0_SPLIT.HCMP1 on PB1
};

void stop_motor(Motor* motor) {
    if (!motor) { return; }
    // set the fwd pin of the motor LOW
    *motor->fwd_port &= ~motor->fwd_pin;
    // set the rev pin of the motor LOW
    *motor->rev_port &= ~motor->rev_pin;
}

void start_motor(Motor* motor, bool direction) {
    if (!motor) { return; }
    if (direction) {
        // set the fwd pin of the motor HIGH
        *motor->fwd_port |= motor->fwd_pin;
        // set the rev pin of the motor LOW
        *motor->rev_port &= ~motor->rev_pin;
    } else {
        // set the fwd pin of the motor LOW
        *motor->fwd_port &= ~motor->fwd_pin;
        // set the rev pin of the motor HIGH
        *motor->rev_port |= motor->rev_pin;
    }
}

void init_motors(void) {
    // use TCA0 for PB0 and PB1
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTB_gc;
    // enable PB0 & PB1 as outputs
    PORTB.DIRSET = PIN0_bm | PIN1_bm;
    // split-mode, enable compare outputs
    TCA0.SINGLE.CTRLD = TCA_SPLIT_SPLITM_bm;
    TCA0.SPLIT.CTRLB = TCA_SPLIT_LCMP0EN_bm | TCA_SPLIT_LCMP1EN_bm;
    // set full 8-bit period
    TCA0.SPLIT.LPER = 255;
    // set duty to 4V out of 5V
    TCA0.SPLIT.LCMP0 = 4 * 51;
    TCA0.SPLIT.LCMP1 = 4 * 51;
    // use a prescaler of DIV64 and enable clock
    TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV64_gc | TCA_SPLIT_ENABLE_bm;
    // Enable PE0, PE1 for left motor and PA1, PE3 for right motor direction pins
    PORTE.DIRSET = PIN0_bm | PIN1_bm | PIN3_bm;
    PORTA.DIRSET = PIN1_bm;
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}
