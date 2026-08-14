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



#endif