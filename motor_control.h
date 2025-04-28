/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef MOTOR_CONTROL_H
#define	MOTOR_CONTROL_H

#include <xc.h> 

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void motor_setup(void);
void move_forward(uint8_t speed_percent);
void move_backward(uint8_t speed_percent);
void turn_right(uint8_t speed_percent);
void turn_left(uint8_t speed_percent);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* MOTOR_CONTROL_H */

