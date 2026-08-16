/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
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

/* USER CODE END Variables */
/* Definitions for WaterTask */
osThreadId_t WaterTaskHandle;
const osThreadAttr_t WaterTask_attributes = {
  .name = "WaterTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for BeepTask */
osThreadId_t BeepTaskHandle;
uint32_t BeepTaskBuffer[ 128 ];
osStaticThreadDef_t BeepTaskControlBlock;
const osThreadAttr_t BeepTask_attributes = {
  .name = "BeepTask",
  .cb_mem = &BeepTaskControlBlock,
  .cb_size = sizeof(BeepTaskControlBlock),
  .stack_mem = &BeepTaskBuffer[0],
  .stack_size = sizeof(BeepTaskBuffer),
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for NoiseTask */
osThreadId_t NoiseTaskHandle;
const osThreadAttr_t NoiseTask_attributes = {
  .name = "NoiseTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow2,
};
/* Definitions for BreatheTask */
osThreadId_t BreatheTaskHandle;
const osThreadAttr_t BreatheTask_attributes = {
  .name = "BreatheTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Water_Task(void *argument);
void Beep_Task(void *argument);
void Noise_Task(void *argument);
void Breathe_Task(void *argument);

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of WaterTask */
  WaterTaskHandle = osThreadNew(Water_Task, NULL, &WaterTask_attributes);

  /* creation of BeepTask */
  BeepTaskHandle = osThreadNew(Beep_Task, NULL, &BeepTask_attributes);

  /* creation of NoiseTask */
  NoiseTaskHandle = osThreadNew(Noise_Task, NULL, &NoiseTask_attributes);

  /* creation of BreatheTask */
  BreatheTaskHandle = osThreadNew(Breathe_Task, NULL, &BreatheTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Water_Task */
/**
  * @brief  Function implementing the WaterTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Water_Task */
__weak void Water_Task(void *argument)
{
  /* USER CODE BEGIN Water_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Water_Task */
}

/* USER CODE BEGIN Header_Beep_Task */
/**
* @brief Function implementing the BeepTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Beep_Task */
__weak void Beep_Task(void *argument)
{
  /* USER CODE BEGIN Beep_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Beep_Task */
}

/* USER CODE BEGIN Header_Noise_Task */
/**
* @brief Function implementing the NoiseTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Noise_Task */
__weak void Noise_Task(void *argument)
{
  /* USER CODE BEGIN Noise_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Noise_Task */
}

/* USER CODE BEGIN Header_Breathe_Task */
/**
* @brief Function implementing the BreatheTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Breathe_Task */
__weak void Breathe_Task(void *argument)
{
  /* USER CODE BEGIN Breathe_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Breathe_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

