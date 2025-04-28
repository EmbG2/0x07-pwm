#include "xc.h"
#include "pwm.h"
#include <stdint.h>

#define FCY 72000000UL  // 72 MHz clock
#define PWM_FREQ 10000  // 10 kHz
#define PWM_PERIOD ((FCY / PWM_FREQ) - 1)  // Formula for period

int main(void) {
    // Example assumes OC1 used for motor control

    // Set PWM period (for internal clock mode, OCxRS is period)
    OC1R = 0;                   // Start duty at 0
    OC1RS = PWM_PERIOD;         // Set period for 10 kHz

    pwm_init(1);                // Initialize OC1
    pwm_set_duty(1, PWM_PERIOD * 0.5); // 50% duty cycle for testing
    pwm_start(1);               // Start PWM output on OC1

    while(1) {
        // Infinite loop, PWM running in hardware
        // Add logic here (e.g., check button and change duty)
    }
}
