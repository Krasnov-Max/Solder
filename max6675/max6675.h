#include "stm32f3xx_hal.h"
#include "main.h"

#define PORT_MAX6675 GPIOB
#define MAX6675_CS   GPIO_PIN_1 
#define MAX6675_SCK  GPIO_PIN_0
#define MAX6675_MOSI GPIO_PIN_2

void MAX6675_Init( void );
float MAX6675_Temp( void ); 


