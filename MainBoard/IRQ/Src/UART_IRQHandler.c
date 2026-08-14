#include "UART_IRQHandler.h"
#include "CAN_IRQHandler.h"

uint8_t rx_buffer[5] = {0};
volatile uint8_t TxData[3] = {0};

void UART_Start_Receive(void)
{
    HAL_UART_Receive_IT(&huart1, rx_buffer, 5);
    TxData[0] = rx_buffer[1];
    TxData[1] = rx_buffer[2];
    TxData[2] = rx_buffer[3];
    CAN_Send_Message(0x02010101, 3, TxData);
}
