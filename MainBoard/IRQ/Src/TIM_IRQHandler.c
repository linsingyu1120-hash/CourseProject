#include "TIM_IRQHandler.h"

static uint8_t dir = 1;
uint8_t breathe_is_on = 0;
volatile uint8_t rx_buffer[5];
static uint16_t tim_count = 0;
volatile uint32_t breathe_led_period;

void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if ((htim->Instance != TIM2) || (breathe_is_on != 1))
    {
        return;
    }

    breathe_led_period = ((uint32_t)rx_buffer[2] << 8) | (uint32_t)rx_buffer[3];

    if (dir == 1)
    {

        tim_count = tim_count + 400 / breathe_led_period;
    }
    else
    {
        tim_count = tim_count - 400 / breathe_led_period;
    }

    if (tim_count >= 1000)
    {
        dir = 0;
    }
    else if (tim_count == 0)
    {
        dir = 1;
    }
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, tim_count);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, tim_count);
}
