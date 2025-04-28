#include "driving.h"

#include <util/delay.h>

static void delay_ms_var(uint16_t ms) {
    while (ms--) { _delay_ms(1); }
}

void drive_time(uint16_t duration, bool forward) {
    start_motor(&left_motor, forward);
    start_motor(&right_motor, forward);
    delay_ms_var(duration);
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}

void turn_time(uint16_t duration, bool clockwise) {
    start_motor(&left_motor, clockwise);
    start_motor(&right_motor, !clockwise);
    delay_ms_var(duration);
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}

void drive_counts(uint16_t enc_count, bool forward) {
    cli(); // disable interrupts
    right_enc = 0;
    left_enc = 0;
    sei(); // re-enable interrupts
    start_motor(&left_motor, forward);
    start_motor(&right_motor, forward);
    while (left_enc < enc_count || right_enc < enc_count) {
        _delay_ms(1);
    }
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}

void turn_counts(uint16_t enc_count, bool clockwise) {
    cli(); // disable interrupts
    right_enc = 0;
    left_enc = 0;
    sei(); // re-enable interrupts
    start_motor(&left_motor, clockwise);
    start_motor(&right_motor, !clockwise);
    while (left_enc < enc_count || right_enc < enc_count) {
        _delay_ms(1);
    }
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}

