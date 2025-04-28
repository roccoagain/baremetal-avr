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
    right_motor.enc = 0;
    left_motor.enc = 0;
    sei(); // re-enable interrupts
    start_motor(&left_motor, forward);
    start_motor(&right_motor, forward);
    while (left_motor.enc < enc_count || right_motor.enc < enc_count) {
        _delay_ms(1);
    }
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}

void turn_counts(uint16_t enc_count, bool clockwise) {
    cli(); // disable interrupts
    right_motor.enc = 0;
    left_motor.enc = 0;
    sei(); // re-enable interrupts
    start_motor(&left_motor, clockwise);
    start_motor(&right_motor, !clockwise);
    while (left_motor.enc < enc_count || right_motor.enc < enc_count) {
        _delay_ms(1);
    }
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}

void drive_distance(uint16_t feet, bool forward) {
    uint16_t enc_counts = feet * TICKS_PER_FOOT;
    drive_counts(enc_counts, forward);
}

void turn_degrees(uint16_t degrees, bool clockwise) {
    uint16_t enc_counts = degrees * TICKS_PER_DEGREE;
    turn_counts(enc_counts, clockwise);
}
