#include "max6675.h"
#include "stm32f3xx_hal.h"

void MAX6675_Init( void ) 
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = Temperature_SCK_Pin|Touch_SCK_Pin|Touch_MOSI_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  	GPIO_InitStruct.Pull = GPIO_NOPULL;
  	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(PORT_MAX6675, MAX6675_CS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_MAX6675, MAX6675_SCK, GPIO_PIN_SET);
}

float MAX6675_Temp( void )
{
	uint16_t temp = 0;
	unsigned char i;
	HAL_GPIO_WritePin(PORT_MAX6675, MAX6675_CS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PORT_MAX6675, MAX6675_SCK, GPIO_PIN_RESET);			 
	for(i=0; i<16; i++)
		{
			temp<<=1;
			temp|= HAL_GPIO_ReadPin(PORT_MAX6675, MAX6675_MOSI); 
			HAL_GPIO_WritePin(PORT_MAX6675, MAX6675_SCK, GPIO_PIN_SET);			 
			HAL_GPIO_WritePin(PORT_MAX6675, MAX6675_SCK, GPIO_PIN_RESET);			 
		}
	HAL_GPIO_WritePin(PORT_MAX6675, MAX6675_CS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_MAX6675, MAX6675_SCK, GPIO_PIN_SET);	
	return ((temp >> 3) * 0.25);
}