#include <avr/io.h>
#include <util/delay.h>

void setup(void) {
    // Set PE2 (D13) as output
    PORTE.DIRSET = PIN2_bm;
}

void loop(void) {
    // Toggle PE2 (D13)
    PORTE.OUTTGL = PIN2_bm;
    _delay_ms(500);
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
}
