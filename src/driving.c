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
    while (1) {
        uint16_t left, right;
        cli();
        left = left_motor.enc;
        right = right_motor.enc;
        sei();
        if (left >= enc_count && right >= enc_count) {
            break;
        }
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
    while (1) {
        uint16_t left, right;
        cli();
        left = left_motor.enc;
        right = right_motor.enc;
        sei();
        if (left >= enc_count && right >= enc_count) {
            break;
        }
        _delay_ms(1);
    }
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}

void drive_distance(uint16_t feet, bool forward) {
    uint16_t enc_counts = (uint16_t)(feet * TICKS_PER_FOOT);
    drive_counts(enc_counts, forward);
    _delay_ms(AFTER_MOVE_DELAY);
}

void turn_degrees(uint16_t degrees, bool clockwise) {
    uint16_t enc_counts = (uint16_t)(degrees * TICKS_PER_DEGREE);
    turn_counts(enc_counts, clockwise);
    _delay_ms(AFTER_MOVE_DELAY);
}
