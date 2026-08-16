#include "myostask.h"
#include "beep.h"

volatile uint32_t waterTaskStackHighWaterMark = 0;
volatile uint32_t beepTaskStackHighWaterMark = 0;

void Water_Task(void *argument)
{
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);

    for (;;)
    {
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
        osDelay(250);
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);

        waterTaskStackHighWaterMark = uxTaskGetStackHighWaterMark(NULL) * sizeof(StackType_t);

        osDelay(250);
    }
}

void Beep_Task(void *argument)
{
    beep_init();

    for (;;)
{
    if (beep_times != 0U)
    {
        beep(beep_times);
        beep_times = 0U;
    }

    beepTaskStackHighWaterMark =
        uxTaskGetStackHighWaterMark(NULL) * sizeof(StackType_t);

    osDelay(10U);
}
}
