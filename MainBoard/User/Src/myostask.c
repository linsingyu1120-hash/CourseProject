#include "myostask.h"
#include "beep.h"
#include "CAN_IRQHandler.h"

volatile uint32_t waterTaskStackHighWaterMark = 0;
volatile uint32_t beepTaskStackHighWaterMark = 0;
volatile uint32_t noiseTaskStackHighWaterMark = 0;

static uint8_t dir = 1U;
static uint16_t tim_count = 0U;
volatile uint8_t breathe_is_on = 0U;
volatile uint32_t breathe_led_period = 0U;
static uint32_t id = 0x000;
static uint8_t TxData[8] = {0};
static uint32_t TxData[8] = {0};

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

void Noise_Task(void *argument)
{
    id++;
    if (id == 0x012)
    {
        id = 0x013;
    }

    (void)CAN_Send_Message(id, 3U, TxData);

    noiseTaskStackHighWaterMark =
        uxTaskGetStackHighWaterMark(NULL) * sizeof(StackType_t);

    osDelay(2U);
}
