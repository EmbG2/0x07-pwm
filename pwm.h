/* 
 * File:   pwm.h
 * Author: EmbeddedG2
 * Comments: PWM control using Output Compare on dsPIC33
 * Revision history: 
 */

#ifndef PWM_H
#define PWM_H

#include <xc.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void pwm_init(uint8_t oc_module);
void pwm_set_duty(uint8_t oc_module, uint16_t duty_cycle);
void pwm_start(uint8_t oc_module);
void pwm_stop(uint8_t oc_module);

#ifdef __cplusplus
}
#endif

#endif /* PWM_H */
