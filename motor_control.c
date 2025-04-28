/*
 * File:   motor_control.c
 * Author: shady
 *
 * Created on April 28, 2025, 6:29 PM
 */


#include "xc.h"
#include "pwm.h"

#define FCY 72000000UL
#define PWM_FREQ 10000
#define PWM_PERIOD ((FCY / PWM_FREQ) - 1)


static uint16_t percent_to_duty(uint8_t percent) {
    if (percent > 100) percent = 100;
    return (uint16_t)((PWM_PERIOD * percent) / 100);
}


void motor_setup(void) {
    // Map OCx to RP pins
    RPOR0bits.RP65R = 18; // OC1 -> RP65 (RD1) PAGE 97 in datasheet
    RPOR1bits.RP66R = 19; // OC2 -> RP66 (RD2)
    RPOR1bits.RP67R = 20; // OC3 -> RP67 (RD3)
    RPOR2bits.RP68R = 21; // OC4 -> RP68 (RD4) 

    // Set RD1 - RD4 as outputs
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;

    // Set PWM Period for all OC modules
    OC1R = 0;  OC1RS = PWM_PERIOD;
    OC2R = 0;  OC2RS = PWM_PERIOD;
    OC3R = 0;  OC3RS = PWM_PERIOD;
    OC4R = 0;  OC4RS = PWM_PERIOD;

    // Initialize all PWM modules
    pwm_init(1);
    pwm_init(2);
    pwm_init(3);
    pwm_init(4);

    // Set initial duty cycles (for example, 0 to keep motors off)
    pwm_set_duty(1, 0);
    pwm_set_duty(2, 0);
    pwm_set_duty(3, 0);
    pwm_set_duty(4, 0);

    // Start all PWM
    pwm_start(1);
    pwm_start(2);
    pwm_start(3);
    pwm_start(4);
}

void move_forward(uint8_t speed_percent) {
    uint16_t duty = percent_to_duty(speed_percent);

    pwm_set_duty(1, 0);    // A OFF
    pwm_set_duty(2, duty); // B ON (left motor forward)
    pwm_set_duty(3, 0);    // C OFF
    pwm_set_duty(4, duty); // D ON (right motor forward)
}

void move_backward(uint8_t speed_percent) {
    uint16_t duty = percent_to_duty(speed_percent);

    pwm_set_duty(1, duty); // A ON (left motor backward)
    pwm_set_duty(2, 0);    // B OFF
    pwm_set_duty(3, duty); // C ON (right motor backward)
    pwm_set_duty(4, 0);    // D OFF
}

void turn_right(uint8_t speed_percent) {
    uint16_t duty_high = percent_to_duty(speed_percent);         // left motor stronger
    uint16_t duty_low = percent_to_duty(speed_percent * 70 / 100); // right motor slower (70% of left)

    pwm_set_duty(1, 0);        // A OFF
    pwm_set_duty(2, duty_high); // B ON (left motor forward, faster)
    pwm_set_duty(3, 0);        // C OFF
    pwm_set_duty(4, duty_low); // D ON (right motor forward, slower)
}

void turn_left(uint8_t speed_percent) {
    uint16_t duty_high = percent_to_duty(speed_percent);
    uint16_t duty_low = percent_to_duty(speed_percent * 70 / 100);

    pwm_set_duty(1, 0);
    pwm_set_duty(2, duty_low);    // B ON (left motor forward, slower)
    pwm_set_duty(3, 0);
    pwm_set_duty(4, duty_high);   // D ON (right motor forward, faster)
}

void stop_motors(void) {
    pwm_set_duty(1, 0);
    pwm_set_duty(2, 0);
    pwm_set_duty(3, 0);
    pwm_set_duty(4, 0);
}