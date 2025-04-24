#include "driving.h"

#include <util/delay.h>

static void delay_ms_var(uint16_t ms) {
    while (ms--) { _delay_ms(1); }
}

void drive_time(uint16_t duration, bool forward) {
    drive_motor(&left_motors, forward);
    drive_motor(&right_motors, forward);
    delay_ms_var(duration);
    stop_motor(&left_motors);
    stop_motor(&right_motors);
}

void turn_time(uint16_t duration, bool clockwise) {
    drive_motor(&left_motors, clockwise);
    drive_motor(&right_motors, !clockwise);
    delay_ms_var(duration);
    stop_motor(&left_motors);
    stop_motor(&right_motors);
}