#include "motor.h"

Motor left_motor = {
    // PE0 is forward
    .fwd_port = &PORTE.OUT,
    .fwd_pin = PIN0_bm,
    // PE1 is reverse
    .rev_port = &PORTE.OUT,
    .rev_pin = PIN1_bm,
    .pwm_reg = &TCA0.SPLIT.LCMP0, // LCMP0 drives WO0 (PB0)
};

Motor right_motor = {
    // PA1 is forward
    .fwd_port = &PORTA.OUT,
    .fwd_pin = PIN1_bm,
    // PE3 is reverse
    .rev_port = &PORTE.OUT,
    .rev_pin = PIN3_bm,
    .pwm_reg = &TCA0.SPLIT.HCMP1, // HCMP1 drives WO1 (PB1)
};

void init_motors() {
    // enable PB0 & PB1 as outputs
    PORTB.DIRSET = PIN0_bm | PIN1_bm;
    // split‑mode, enable compare outputs
    TCA0.SINGLE.CTRLD = TCA_SPLIT_SPLITM_bm;
    TCA0.SPLIT.CTRLB = TCA_SPLIT_LCMP0EN_bm | TCA_SPLIT_HCMP1EN_bm;
    // full 8‑bit period
    TCA0.SPLIT.LPER = 255;
    TCA0.SPLIT.HPER = 255;
    // default duty (≈ 3/255), adjust later per‑motor
    TCA0.SPLIT.LCMP0 = 3 * 51;
    TCA0.SPLIT.HCMP1 = 3 * 51;
    // run at CLK_PER/64, enable timer
    TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV64_gc | TCA_SPLIT_ENABLE_bm;

    // Enable PE0, PE1 for left motor and PA1, PE3 for right motor
    PORTE.DIRSET = PIN0_bm | PIN1_bm | PIN3_bm;
    PORTA.DIRSET = PIN1_bm;
}


void stop_motor(Motor* motor) {
    // disable both direction lines
    *motor->fwd_port &= ~motor->fwd_pin;
    *motor->rev_port &= ~motor->rev_pin;
}
