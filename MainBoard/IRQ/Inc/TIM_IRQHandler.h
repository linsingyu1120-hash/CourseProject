#ifndef TIM_IRQHandler_H
#define TIM_IRQHandler_H

/*---------------------------------Include--------------------------------*/
#include "main.h"
#include "tim.h"

/*---------------------------------Define---------------------------------*/
extern volatile uint16_t tim_count;
extern volatile uint8_t dir;

/*---------------------------------Function-------------------------------*/
void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /*TIM_IRQHandler_H*/