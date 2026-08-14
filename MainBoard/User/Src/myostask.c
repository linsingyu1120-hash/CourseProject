#include "myostask.h"

volatile uint32_t waterTaskStackHighWaterMark = 0;

void Water_Task(void *argument)
{
    water_init();
    for(;;)
    {
        led_on(1);
        led_off(2);
        osDelay(250);
        led_off(1);
        led_on(2);
        osDelay(250);

        waterTaskStackHighWaterMark = uxTaskGetStackHighWaterMark(NULL) * sizeof(StackType_t);
    }
}