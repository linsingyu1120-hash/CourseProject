#include "timer.h"
#include <stdint.h>

uint32_t now_ms;
uint32_t duration_ms;
uint32_t start_ms;
void timer_start(once_timer *timer_ms, uint32_t now_ms,uint32_t duration_ms) 
{
    timer_ms->start_ms = now_ms; 
    timer_ms->duration_ms = duration_ms;  
    timer_ms->running_judge = 1U;  
}

void timer_stop(once_timer *timer_ms)  
{
    timer_ms->running_judge = 0;  
}

uint8_t timer_is_expired(once_timer *timer_ms, uint32_t now_ms) 
{
    if (timer_ms->running_judge &&((now_ms - timer_ms->start_ms) >= timer_ms->duration_ms))  
    {
        timer_ms->running_judge = 0;  
        return 1;
    }

    return 0;
}