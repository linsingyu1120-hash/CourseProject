#include "TIM_IRQHandler.h"
#include "beep.h"

static uint8_t dir = 1U;
static uint16_t tim_count = 0U;
volatile uint8_t breathe_is_on = 0U;
volatile uint32_t breathe_led_period = 0U;
static uint32_t id = 0x013;
static uint8_t TxData[8] = {0};

void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance != TIM2)
    {
        return;
    }

    if ((breathe_is_on != 1U) || (breathe_led_period < 4U))
    {
        tim_count = 0U;
        dir = 1U;
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0U);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0U);
        return;
    }

    if ((uint32_t)tim_count > (breathe_led_period / 2U))
    {
        tim_count = (uint16_t)(breathe_led_period / 2U);
    }

    if (dir == 1U)
    {
        if (((uint32_t)tim_count + 2U) >= (breathe_led_period / 2U))
        {
            tim_count = (uint16_t)(breathe_led_period / 2U);
            dir = 0U;
        }
        else
        {
            tim_count += 2U;
        }
    }
    else
    {
        if (tim_count <= 2U)
        {
            tim_count = 0U;
            dir = 1U;
        }
        else
        {
            tim_count -= 2U;
        }
    }

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ((uint32_t)tim_count * 999U) / (breathe_led_period / 2U));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ((uint32_t)tim_count * 999U) / (breathe_led_period / 2U));
}