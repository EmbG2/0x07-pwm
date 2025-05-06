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
    RPOR0bits.RP65R = 0b010000; // OC1 -> RP65 (RD1)  page 97 in datasheet
    RPOR1bits.RP66R = 0b010001; // OC2 -> RP66 (RD2)
    RPOR1bits.RP67R = 0b010010; // OC3 -> RP67 (RD3)
    RPOR2bits.RP68R = 0b010011; // OC4 -> RP68 (RD4)

    // Set RD1 - RD4 as outputs
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;

    // Initialize all PWM modules with 50% duty cycle
    pwm_init(1, PWM_PERIOD, PWM_PERIOD / 2);
    pwm_init(2, PWM_PERIOD, PWM_PERIOD / 2);
    pwm_init(3, PWM_PERIOD, PWM_PERIOD / 2);
    pwm_init(4, PWM_PERIOD, PWM_PERIOD / 2);

    // Start all PWM modules
    pwm_start(1);
    pwm_start(2);
    pwm_start(3);
    pwm_start(4);

    // Set initial duty cycles to 0
    pwm_set_duty(1, 0);
    pwm_set_duty(2, 0);
    pwm_set_duty(3, 0);
    pwm_set_duty(4, 0);
}

void move_forward(uint8_t speed_percent) {
    uint16_t duty = percent_to_duty(speed_percent);
    pwm_set_duty(1, 0);
    pwm_set_duty(2, duty);
    pwm_set_duty(3, 0);
    pwm_set_duty(4, duty);
}

void move_backward(uint8_t speed_percent) {
    uint16_t duty = percent_to_duty(speed_percent);
    pwm_set_duty(1, duty);
    pwm_set_duty(2, 0);
    pwm_set_duty(3, duty);
    pwm_set_duty(4, 0);
}

void turn_right(uint8_t speed_percent) {
    uint16_t duty_high = percent_to_duty(speed_percent);
    uint16_t duty_low = percent_to_duty(speed_percent * 70 / 100);
    pwm_set_duty(1, 0);
    pwm_set_duty(2, duty_high);
    pwm_set_duty(3, 0);
    pwm_set_duty(4, duty_low);
}

void turn_left(uint8_t speed_percent) {
    uint16_t duty_high = percent_to_duty(speed_percent);
    uint16_t duty_low = percent_to_duty(speed_percent * 70 / 100);
    pwm_set_duty(1, 0);
    pwm_set_duty(2, duty_low);
    pwm_set_duty(3, 0);
    pwm_set_duty(4, duty_high);
}

void stop_motors(void) {
    pwm_set_duty(1, 0);
    pwm_set_duty(2, 0);
    pwm_set_duty(3, 0);
    pwm_set_duty(4, 0);
}
