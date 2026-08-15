#ifndef MYOSTASK_H
#define MYOSTASK_H

#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"

#define LED_ON(x) HAL_GPIO_WritePin(LED_##x##_GPIO_Port, LED_##x##_Pin, GPIO_PIN_SET)
#define LED_OFF(x) HAL_GPIO_WritePin(LED_##x##_GPIO_Port, LED_##x##_Pin, GPIO_PIN_RESET)

void Water_Task(void *argument);

#endif