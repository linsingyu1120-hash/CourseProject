#include "wave.h"
#include "usart.h"
#include "beep.h"
#include "CAN_IRQHandler.h"
#include <string.h>

CAN_RxHeaderTypeDef RxHeader;
CAN_TxHeaderTypeDef TxHeader;
uint8_t RxData[8];

float y = 0.0f;
uint32_t TxMailbox;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance != CAN1)
    {
        return;
    }

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    {
        return;
    }

    if ((RxHeader.IDE == CAN_ID_STD) && (RxHeader.StdId == 0x012U) && (RxHeader.DLC == 4U))
    {
        memcpy(&y, RxData, sizeof(float));
        Sine_Wave();
    }
    else if ((RxHeader.IDE == CAN_ID_EXT) && (RxHeader.ExtId == 0x02010102U) && (RxHeader.DLC == 1U))
    {
        beep_initialized = 0U;
        buzzer_is_on = 1U;
        beep_times = RxData[0];
        beep();
    }
}

HAL_StatusTypeDef CAN_Send_Message(uint32_t ExtId, uint8_t DLC, uint8_t *TxData)
{
    TxHeader.ExtId = ExtId;
    TxHeader.IDE = CAN_ID_EXT;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = DLC;
    TxHeader.TransmitGlobalTime = DISABLE;

    return HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
}