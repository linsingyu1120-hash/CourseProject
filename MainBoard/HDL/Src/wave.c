#include "wave.h"
#include "usart.h"
#include "CAN_IRQHandler.h"
#include <string.h>

void Sine_Wave(void)
{
    static uint8_t tx_buffer[8];
    memcpy(tx_buffer, &y, sizeof(y));
    tx_buffer[4] = 0x00;
    tx_buffer[5] = 0x00;
    tx_buffer[6] = 0x80;
    tx_buffer[7] = 0x7F;

    if (HAL_UART_Transmit_IT(&huart1, tx_buffer, sizeof(tx_buffer)) != HAL_OK)
    {
        return;
    }
}