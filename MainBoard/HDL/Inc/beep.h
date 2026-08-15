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
} beep_config;

extern volatile uint8_t beep_initialized;
extern volatile uint8_t beep_times;
extern volatile uint8_t buzzer_is_on;

#define BUZZER_GPIO_PORT BEEP_GPIO_Port
#define BUZZER_PIN BEEP_Pin

void beep(void);
void beep_exit(void);
void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);

#endif
