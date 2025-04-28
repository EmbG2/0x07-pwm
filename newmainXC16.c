#include "xc.h"
#include "motor_control.h"
#include "timer.h"

#define FCY 72000000UL

void setup_button(void) {
    TRISEbits.TRISE8 = 1; // Set RE8 as input
}

#define BUTTON_E8 PORTEbits.RE8

int main(void) {
    motor_setup();
    setup_button();

    uint8_t prev_button = 1;
    uint8_t start_sequence = 0;

    while (1) {
        uint8_t current_button = BUTTON_E8;

        // Detect falling edge: button press
        if (prev_button == 1 && current_button == 0) {
            start_sequence = 1;
            tmr_wait_ms(TIMER2, 200); // de-bouncing
        }

        if (start_sequence) {
            move_forward(50); // Move forward at 50% speed
            tmr_wait_ms(TIMER1, 3000); // Move forward for 3 seconds

            stop_motors();
            tmr_wait_ms(TIMER1, 1000); // Pause 1 second

            move_backward(50); // Move backward at 50% speed
            tmr_wait_ms(TIMER1, 3000); // Move backward for 3 seconds

            stop_motors();

            start_sequence = 0; // Sequence done
        }

        prev_button = current_button;
    }
}
