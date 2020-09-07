/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define KEY_1_Pin GPIO_PIN_3
#define KEY_1_GPIO_Port GPIOA
#define KEY_2_Pin GPIO_PIN_4
#define KEY_2_GPIO_Port GPIOA
#define Hiter_Pin GPIO_PIN_6
#define Hiter_GPIO_Port GPIOA
#define Temperature_SCK_Pin GPIO_PIN_0
#define Temperature_SCK_GPIO_Port GPIOB
#define Temperature_CS_Pin GPIO_PIN_1
#define Temperature_CS_GPIO_Port GPIOB
#define Temperature_IN_Pin GPIO_PIN_2
#define Temperature_IN_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_10
#define LCD_DC_GPIO_Port GPIOB
#define Touch_IRQ_Pin GPIO_PIN_11
#define Touch_IRQ_GPIO_Port GPIOB
#define Touch_CS_Pin GPIO_PIN_12
#define Touch_CS_GPIO_Port GPIOB
#define Touch_SCK_Pin GPIO_PIN_13
#define Touch_SCK_GPIO_Port GPIOB
#define Touch_MISO_Pin GPIO_PIN_14
#define Touch_MISO_GPIO_Port GPIOB
#define Touch_MOSI_Pin GPIO_PIN_15
#define Touch_MOSI_GPIO_Port GPIOB
#define Memory_CS_Pin GPIO_PIN_9
#define Memory_CS_GPIO_Port GPIOA
#define BackLight_Pin GPIO_PIN_10
#define BackLight_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_11
#define Buzzer_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_8
#define LCD_CS_GPIO_Port GPIOB
#define LCD_Reset_Pin GPIO_PIN_9
#define LCD_Reset_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define MIN_PID 50
#define MAX_PID 900
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
