#ifndef TIM_IRQHandler_H
#define TIM_IRQHandler_H

#include "main.h"
#include "tim.h"

void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern volatile uint8_t breathe_is_on;
extern volatile uint32_t breathe_led_period;

#endif /*TIM_IRQHandler_H*/