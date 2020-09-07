#include "pid.h"



void pid_controller_init(pid_controller_t* controller, float kp, float ki, float kd, uint16_t min, uint16_t max)	
{
    controller->value = 0;
	  controller->e[0] = controller->e[2] =controller->e[2] = 0;
	  controller->un = controller->un_1 = 0;
		controller->i = 0;
		controller->p = 0;
		controller->d = 0;
	  controller->ki = ki;
	  controller->kd = kd;
    controller->kp = kp;
	  controller->min = min;
	  controller->max = max;
}

void pid_controller_reset(pid_controller_t* controller, uint16_t min, uint16_t max)
{
   
    controller->value = 0;
	  controller->e[0] = controller->e[2] =controller->e[2] = 0;
	  controller->un = controller->un_1 = 0;
		controller->i = 0;
		controller->p = 0;
		controller->d = 0;
	  controller->min = min;
	  controller->max = max;
}

int16_t pid_controller_calculate(pid_controller_t* controller, float Set_Current, float Current )
{
    float  tmp;
    controller->e[2] = controller->e[1];
	  controller->e[1] = controller->e[0];
	  controller->e[0] = Set_Current - Current;
	  controller->un_1 = controller->un;
    // P = Kp * (e(n) - e(n-1));
    controller->p = controller->kp * (controller->e[0] - controller->e[1]);
    // I = Ki * e(n);
    controller->i = controller->ki * controller->e[0];
    // D = Kd * (e(t) - e(t-1));
    controller->d = controller->kd * (controller->e[0] - (2*controller->e[1])+controller->e[2]);
	  // U(n) = U(n-1)+P+I+D
    controller->un = controller->un_1+ controller->p + controller->i + controller->d;
	  tmp = controller->un; 
	  if (tmp >= controller->max) tmp = controller->max;
    if (tmp <= controller->min) tmp = controller->min;   
	  if (tmp == 0) tmp = 1;
	  if (tmp <= -1 ) tmp = 1;
    controller->value = tmp;
    return 1;
}