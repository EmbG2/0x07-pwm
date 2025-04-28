/*
 * File:   pwm.c
 * Author: EmbeddedG2
 *
 * Created on April 28, 2025, 4:53 PM
 */

#include "pwm.h"

void pwm_init(uint8_t oc_module) {
    switch (oc_module) {
        case 1:
            OC1CON1bits.OCM = 0b000;    // Disable Output Compare module
            OC1CON1bits.OCTSEL = 0b111; // Peripheral clock source (internal clock)
            OC1CON2bits.SYNCSEL = 0x1F; // No sync (OCxRS acts as period)
            OC1CON1bits.OCM = 0b110;    // Edge-aligned PWM mode
            break;
        case 2:
            OC2CON1bits.OCM = 0b000;
            OC2CON1bits.OCTSEL = 0b111;
            OC2CON2bits.SYNCSEL = 0x1F;
            OC2CON1bits.OCM = 0b110;
            break;
        case 3:
            OC3CON1bits.OCM = 0b000;
            OC3CON1bits.OCTSEL = 0b111;
            OC3CON2bits.SYNCSEL = 0x1F;
            OC3CON1bits.OCM = 0b110;
            break;
        case 4:
            OC4CON1bits.OCM = 0b000;
            OC4CON1bits.OCTSEL = 0b111;
            OC4CON2bits.SYNCSEL = 0x1F;
            OC4CON1bits.OCM = 0b110;
            break;
        default:
            // Invalid OC module
            break;
    }
}

void pwm_set_duty(uint8_t oc_module, uint16_t duty_cycle) {
    switch (oc_module) {
        case 1:
            OC1RS = duty_cycle;
            break;
        case 2:
            OC2RS = duty_cycle;
            break;
        case 3:
            OC3RS = duty_cycle;
            break;
        case 4:
            OC4RS = duty_cycle;
            break;
        default:
            break;
    }
}

void pwm_start(uint8_t oc_module) {
    switch (oc_module) {
        case 1:
            OC1CON1bits.OCM = 0b110; // Enable PWM mode on OC1
            break;
        case 2:
            OC2CON1bits.OCM = 0b110;
            break;
        case 3:
            OC3CON1bits.OCM = 0b110;
            break;
        case 4:
            OC4CON1bits.OCM = 0b110;
            break;
        default:
            break;
    }
}

void pwm_stop(uint8_t oc_module) {
    switch (oc_module) {
        case 1:
            OC1CON1bits.OCM = 0b000; // Disable OC1
            break;
        case 2:
            OC2CON1bits.OCM = 0b000;
            break;
        case 3:
            OC3CON1bits.OCM = 0b000;
            break;
        case 4:
            OC4CON1bits.OCM = 0b000;
            break;
        default:
            break;
    }
}

