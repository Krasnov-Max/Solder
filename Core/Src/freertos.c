/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_Touchscreen.h"
#include "max6675.h"
//#include <stdio.h>
//#include <stdarg.h>
#include "pid.h"
#include "usart.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern pid_controller_t pid;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LCD_OUTHandle;
osThreadId GetTemperatureHandle;
osThreadId EncHandle;
osThreadId ButtonHandle;
osThreadId PIDHandle;
osThreadId SetValueHandle;
osMessageQId ValuePowerHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void LCD_TASK(void const * argument);
void GetTemp(void const * argument);
void GetEnc(void const * argument);
void ButtonState(void const * argument);
void CalcPID(void const * argument);
void SetValuePower(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of ValuePower */
  osMessageQDef(ValuePower, 2, uint16_t);
  ValuePowerHandle = osMessageCreate(osMessageQ(ValuePower), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityLow, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LCD_OUT */
  osThreadDef(LCD_OUT, LCD_TASK, osPriorityLow, 0, 256);
  LCD_OUTHandle = osThreadCreate(osThread(LCD_OUT), NULL);

  /* definition and creation of GetTemperature */
  osThreadDef(GetTemperature, GetTemp, osPriorityAboveNormal, 0, 256);
  GetTemperatureHandle = osThreadCreate(osThread(GetTemperature), NULL);

  /* definition and creation of Enc */
  osThreadDef(Enc, GetEnc, osPriorityNormal, 0, 128);
  EncHandle = osThreadCreate(osThread(Enc), NULL);

  /* definition and creation of Button */
  osThreadDef(Button, ButtonState, osPriorityNormal, 0, 128);
  ButtonHandle = osThreadCreate(osThread(Button), NULL);

  /* definition and creation of PID */
  osThreadDef(PID, CalcPID, osPriorityNormal, 0, 1024);
  PIDHandle = osThreadCreate(osThread(PID), NULL);

  /* definition and creation of SetValue */
  osThreadDef(SetValue, SetValuePower, osPriorityNormal, 0, 128);
  SetValueHandle = osThreadCreate(osThread(SetValue), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
   // HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LCD_TASK */
/**
* @brief Function implementing the LCD_OUT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LCD_TASK */
void LCD_TASK(void const * argument)
{
  /* USER CODE BEGIN LCD_TASK */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LCD_TASK */
}

/* USER CODE BEGIN Header_GetTemp */
/**
* @brief Function implementing the GetTemperature thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GetTemp */
void GetTemp(void const * argument)
{
  /* USER CODE BEGIN GetTemp */
  volatile float tmp;
  extern volatile uint16_t CurrentTemp;
  char buf[20];
  /* Infinite loop */
  for(;;)
  {
    tmp = MAX6675_Temp(); 

    sprintf(buf,"Temp = %d C",  (uint16_t)tmp);
    ILI9341_Draw_Text(buf, 0,0,BLUE,4,WHITE);
     CurrentTemp = tmp;
    osDelay(1000);
  }
  /* USER CODE END GetTemp */
}

/* USER CODE BEGIN Header_GetEnc */
/**
* @brief Function implementing the Enc thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GetEnc */
void GetEnc(void const * argument)
{
  /* USER CODE BEGIN GetEnc */
 uint16_t last=0, tmp; 
 extern TIM_HandleTypeDef htim2;
 char buf[20];
uint16_t i, count;
extern  uint16_t SetTemp;
  /* Infinite loop */
  for(;;)
    {
      tmp = TIM2->CNT;
      if (tmp !=last)
        {
          if (TIM2->CR1 & TIM_CR1_DIR) {SetTemp--;} else {SetTemp++;}
          if (SetTemp<1) {SetTemp=0;}
          if (SetTemp>=350) {SetTemp=350;}
          last = tmp;
          osMessagePut(ValuePowerHandle,SetTemp,100);
          count = sprintf(buf,"Set Temp = %d temp = %d last = %d \n\r ", SetTemp, tmp, last);
          HAL_UART_Transmit(&huart1,(uint8_t*)buf,count,100);
        }
    //vTaskDelay(10);
    taskYIELD();
  }
  /* USER CODE END GetEnc */
}

/* USER CODE BEGIN Header_ButtonState */
/**
* @brief Function implementing the Button thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ButtonState */
void ButtonState(void const * argument)
{
  /* USER CODE BEGIN ButtonState */
  uint8_t key1_stat, key2_stat, last_key1_stat, last_key2_stat;
  /* Infinite loop */
  for(;;)
  {
    key1_stat = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
    key2_stat = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
    if (key1_stat == 0) {HAL_GPIO_WritePin(Hiter_GPIO_Port, Hiter_Pin,GPIO_PIN_SET );}
    if (key2_stat == 0) {HAL_GPIO_WritePin(Hiter_GPIO_Port, Hiter_Pin,GPIO_PIN_RESET );}
    osDelay(20);
  }
  /* USER CODE END ButtonState */
}

/* USER CODE BEGIN Header_CalcPID */
/**
* @brief Function implementing the PID thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CalcPID */
void CalcPID(void const * argument)
{
  /* USER CODE BEGIN CalcPID */
  uint16_t val;
  char buf[20];
  uint8_t count;
  uint16_t tmp, last;
  extern volatile uint16_t CurrentTemp;
  extern  pid_controller_t pid;
  osEvent event;
  //extern UART_HandleTypeDef huart1;
  /* Infinite loop */
  for(;;)
    {
      event = osMessageGet(ValuePowerHandle, 100);
      if (event.status == osEventMessage)
        {
          tmp = event.value.v;
        }
      taskENTER_CRITICAL();  
      val = pid_controller_calculate(&pid, tmp, CurrentTemp );  
      if (last != tmp) 
        {
          pid_controller_reset(&pid, MIN_PID, MAX_PID);
          last = tmp;
        } 
      TIM3->ARR = ((pid.value-MAX_PID)*-1)+1;
      taskEXIT_CRITICAL(); 
      count = sprintf(buf,"Set temp =%d Pid Val = %d , TIM3 val = %ld \n\r ", tmp, pid.value, TIM3->ARR);
      HAL_UART_Transmit(&huart1,(uint8_t*)buf,count,100);
      osDelay(100);
    }
  /* USER CODE END CalcPID */
}

/* USER CODE BEGIN Header_SetValuePower */
/**
* @brief Function implementing the SetValue thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SetValuePower */
void SetValuePower(void const * argument)
{
  /* USER CODE BEGIN SetValuePower */
  
  char buf[20];
  uint8_t count;
  uint16_t tmp;
  /* Infinite loop */
  for(;;)
  {
    
     //    tmp = 
     //    TIM3->ARR = ((tmp-950)*-1)+1;
     //      count = sprintf(buf,"Pid Val = %d  TIM3 = %d \n\r ", tmp, TIM3->ARR);
     //     HAL_UART_Transmit(&huart1,(uint8_t*)buf,count,100);
    
        //if (TIM3->CR1 == 0)
        //  {
            //TIM3->ARR = tmp;
        //  }
     // }
    
    taskYIELD();  
    osDelay(1);
  }
  /* USER CODE END SetValuePower */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
