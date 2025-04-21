#include <avr/io.h>

#include "motor.h"
#include "setup.h"

int main(void) {
    setup_pwm();

    wait_for_pf4_press();  // Wait for user to press button on pin 6
    while (1) {
        // Add main loop code here if needed

    }
}
