#include "beep.h"
#include "timer.h"

volatile uint8_t beep_initialized = 0U;
volatile uint8_t beep_times = 0U;
volatile uint8_t buzzer_is_on = 0U;
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

void beep_run(uint16_t times)
{
    if (!timer_is_expired(&buzzer_timer, now_ms))
    {
        return;
    }

    if (buzzer_is_on == 1U)
    {
        buzzer_off();
        buzzer_is_on = 0U;

        if (times > 0U)
        {
            times--;
        }

        beep_times = (uint8_t)times;

        if (beep_times == 0U)
        {
            beep_initialized = 0U;
            timer_stop(&buzzer_timer);
        }
        else
        {
            timer_start(&buzzer_timer, now_ms, config_ms.beep_shut);
        }
    }
    else
    {
        buzzer_on();
        buzzer_is_on = 1U;
        timer_start(&buzzer_timer, now_ms, config_ms.beep_sound);
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

    if (beep_times == 0U)
    {
        if ((beep_initialized != 0U) || (buzzer_is_on != 0U))
        {
            beep_exit();
        }

        beep_initialized = 0U;
        return;
    }

    if (beep_initialized == 0U)
    {
        beep_exit();
        buzzer_on();
        buzzer_is_on = 1U;
        timer_start(&buzzer_timer, now_ms, config_ms.beep_sound);
        beep_initialized = 1U;
        return;
    }

    beep_run(beep_times);
}