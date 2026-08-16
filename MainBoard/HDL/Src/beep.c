#include "beep.h"

volatile uint8_t beep_times = 0U;

void buzzer_init(void)
{
    buzzer_off();
}

void buzzer_on(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_SET);
}

void buzzer_off(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

void beep_init(void)
{
    buzzer_off();
}

void beep(uint16_t beep_times)
{
    uint16_t i =0;
    for(i=0;i<beep_times;i++)
    {
        buzzer_on();
        HAL_Delay(200);
        buzzer_off();
        HAL_Delay(800);
    }
}