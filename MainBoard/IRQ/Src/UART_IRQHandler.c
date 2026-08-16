#include "UART_IRQHandler.h"
#include "CAN_IRQHandler.h"
#include "TIM_IRQHandler.h"

uint8_t rx_buffer[5] = {0};
uint8_t TxData[3] = {0};

void UART_Start_Receive(void)
{
    HAL_UART_Receive_IT(&huart1, rx_buffer, sizeof(rx_buffer));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {

        if ((rx_buffer[0] == 0xA5U) && (rx_buffer[4] == 0x5AU))
        {
            TxData[0] = rx_buffer[1];
            TxData[1] = rx_buffer[2];
            TxData[2] = rx_buffer[3];

            if (rx_buffer[1] == 0x00U)
            {
                breathe_is_on = 0U;
                (void)CAN_Send_Message(0x012U, 3U, TxData);
            }
            else if ((rx_buffer[1] == 0x01U) && ((rx_buffer[2] >> 4) <= 9U) && ((rx_buffer[2] & 0x0FU) <= 9U) &&
                     ((rx_buffer[3] >> 4) <= 9U) && ((rx_buffer[3] & 0x0FU) <= 9U))
            {
                breathe_led_period = (((uint32_t)rx_buffer[2] >> 4) * 1000U) +
                                     (((uint32_t)rx_buffer[2] & 0x0FU) * 100U) +
                                     (((uint32_t)rx_buffer[3] >> 4) * 10U) + ((uint32_t)rx_buffer[3] & 0x0FU);

                if (breathe_led_period >= 4U)
                {
                    breathe_is_on = 1U;
                    (void)CAN_Send_Message(0x012U, 3U, TxData);
                }
                else
                {
                    breathe_is_on = 0U;
                    TxData[0] = 0x00U;
                    (void)CAN_Send_Message(0x012U, 3U, TxData);
                }
            }
        }
    }

    HAL_UART_Receive_IT(&huart1, rx_buffer, sizeof(rx_buffer));
}
