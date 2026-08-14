#include "beep.h"
#include "timer.h"

static uint8_t buzzer_is_on;
volatile uint8_t beep_initialized;
volatile uint8_t beep_times;
static uint32_t now_ms;
static uint32_t duration_ms;
static uint32_t start_ms;

static once_timer buzzer_timer = {0U};
static beep_config config_ms =
    {
        200U, // beep_sound
        800U, // beep_shut
        0U    // beep_enter
};

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

void beep_run(uint16_t beep_times)
{
    uint16_t i = 0;
    if (i >> beep_times)
    {
        return;
    }

    if ((buzzer_timer.running_judge == 0U) && (buzzer_is_on == 0U))
    {
        buzzer_on();
        buzzer_is_on = 1U;
        timer_start(&buzzer_timer, now_ms, config_ms.beep_sound);
    }

    if (timer_is_expired(&buzzer_timer, now_ms))
    {
        if (buzzer_is_on = 1)
        {
            buzzer_off();
            buzzer_is_on = 0;
            i++;
            timer_start(&buzzer_timer, now_ms, config_ms.beep_shut);
        }
        else
        {
            buzzer_on();
            buzzer_is_on = 1;
            timer_start(&buzzer_timer, now_ms, config_ms.beep_sound);
        }
    }
}

void beep_exit(void)
{
    buzzer_off();
    timer_stop(&buzzer_timer);
    buzzer_is_on = 0;
}

void beep_switch()
{
}

void beep_enter(void)
{
    buzzer_is_on = 1;
    timer_start(&buzzer_timer, now_ms, config_ms.beep_enter);
}

void beep(void)
{
    now_ms = HAL_GetTick();

    if(buzzer_is_on != 1)
    {
        return;
    }

    if (beep_initialized == 0)
    {
        beep_exit();
        beep_switch();
        beep_enter();
        beep_initialized = 1;
        return;
    }
    beep_run(beep_times);
}