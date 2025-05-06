/*
 * File:   pwm.c
 * Author: EmbeddedG2
 *
 * Created on April 28, 2025, 4:53 PM
 */

#include "pwm.h"

void pwm_init(uint8_t oc_module, uint16_t period, uint16_t duty) {
    switch (oc_module) {
        case 1:
            OC1CON1 = 0; OC1CON2 = 0;
            OC1R = duty;
            OC1RS = period;
            OC1CON1bits.OCTSEL = 0x07;
            OC1CON2bits.SYNCSEL = 0x1F;
            break;
        case 2:
            OC2CON1 = 0; OC2CON2 = 0;
            OC2R = duty;
            OC2RS = period;
            OC2CON1bits.OCTSEL = 0x07;
            OC2CON2bits.SYNCSEL = 0x1F;
            break;
        case 3:
            OC3CON1 = 0; OC3CON2 = 0;
            OC3R = duty;
            OC3RS = period;
            OC3CON1bits.OCTSEL = 0x07;
            OC3CON2bits.SYNCSEL = 0x1F;
            break;
        case 4:
            OC4CON1 = 0; OC4CON2 = 0;
            OC4R = duty;
            OC4RS = period;
            OC4CON1bits.OCTSEL = 0x07;
            OC4CON2bits.SYNCSEL = 0x1F;
            break;
        default:
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
            OC1CON1bits.OCM = 0b110;
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
            OC1CON1bits.OCM = 0b000;
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
