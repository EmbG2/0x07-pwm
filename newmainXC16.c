#include "xc.h"
#include "motor_control.h"
#include "timer.h"

#define FCY 72000000UL
#include <libpic30.h>

#define BUTTON_RE8 PORTEbits.RE8

volatile uint8_t moving = 0;

void setup_interrupt_button(void) {
    TRISEbits.TRISE8 = 1;            // Set RE8 as input
    RPINR0bits.INT1R = 88;           // Map INT1 to RPI88 (RE8)
    INTCON2bits.INT1EP = 1;          // Falling edge triggers interrupt
    IFS1bits.INT1IF = 0;             // Clear interrupt flag
    IEC1bits.INT1IE = 1;             // Enable INT1 interrupt
}

int main(void) {
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;

    motor_setup();
    setup_interrupt_button();

    while (1) {}

    return 0;
}

void __attribute__((__interrupt__, auto_psv)) _INT1Interrupt(void) {
    IFS1bits.INT1IF = 0;             // Clear INT1 interrupt flag

    if (!moving) {
        move_forward(70);           // Start motors
        moving = 1;
    } else {
        stop_motors();              // Stop motors
        moving = 0;
    }
}
