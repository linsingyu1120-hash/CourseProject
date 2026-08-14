#ifndef BEEP_H
#define BEEP_H

#include "main.h"
#include "timer.h"

typedef struct 
{
    /* data */
    uint16_t beep_sound;
    uint16_t beep_shut;
    uint16_t beep_enter;
}beep_config;

#ifdef __cplusplus
extern "C" {
#endif
#define BUZZER_GPIO_PORT GPIOB
#define BUZZER_PIN       GPIO_PIN_0
void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);
#ifdef __cplusplus
}
#endif

#endif



