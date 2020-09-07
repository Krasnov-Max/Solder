/**
 * @file pid.h 
 */

#ifndef PID_H
#define	PID_H

#include <stdint.h>
#include "main.h"


typedef struct _PidController {
    float kp; 
    float ki; 
    float kd; 
	  float e[3];
		float p;
		float i;
		float d;
    float un, un_1; 
    uint16_t min; 
    uint16_t max; 
    int16_t value; 
} pid_controller_t;


void pid_controller_init(pid_controller_t* controller, float kp, float ki, float kd, uint16_t min, uint16_t max);	
void pid_controller_reset(pid_controller_t* controller, uint16_t min, uint16_t max);
int16_t pid_controller_calculate(pid_controller_t* controller, float Set_Current, float Current );

#endif	/* PID_H */
