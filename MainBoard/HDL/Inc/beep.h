#ifndef BEEP_H
#define BEEP_H

#include "main.h"

extern volatile uint8_t beep_times;


#define BUZZER_GPIO_PORT BEEP_GPIO_Port
#define BUZZER_PIN BEEP_Pin

void beep(uint16_t beep_times);
void beep_init(void);
void buzzer_on(void);
void buzzer_off(void);


#endif
