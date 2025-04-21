#include "driving.h"

#include <util/delay.h>

static void delay_ms_var(uint16_t ms) {
    while (ms--) {
        _delay_ms(1);
    }
}

void drive(uint16_t duration, bool forward) {
    if (forward == true) {
        drive_motor(&left_motor, true);
        drive_motor(&right_motor, true);
    } else if (forward == false) {
        drive_motor(&left_motor, false);
        drive_motor(&right_motor, false);
    }
    delay_ms_var(duration);
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}

void turn(uint16_t duration, bool clockwise) {
    if (clockwise  == true) {
        drive_motor(&left_motor, true);
        drive_motor(&right_motor, false);
    } else if (clockwise == false) {
        drive_motor(&left_motor, false);
        drive_motor(&right_motor, true);
    }
    delay_ms_var(duration);
    stop_motor(&left_motor);
    stop_motor(&right_motor);
}