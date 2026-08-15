#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct 
{
    /* data */
    uint32_t start_ms;
    uint32_t duration_ms;
    uint32_t running_judge;
}once_timer;

void timer_start(once_timer *timer_ms, uint32_t now_ms, uint32_t duration_ms);
void timer_stop(once_timer *timer_ms);
uint8_t timer_is_expired(once_timer *timer_ms, uint32_t now_ms);

#endif