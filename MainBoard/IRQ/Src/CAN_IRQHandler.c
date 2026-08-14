#include "CAN_IRQHandler.h"
#include "beep.h"
#include "wave.h"

CAN_RxHeaderTypeDef RxHeader;
CAN_TxHeaderTypeDef TxHeader;
uint8_t RxData[8];
uint8_t TxData[8];
uint8_t breathe_is_on = 0;
uint8_t buzzer_is_on = 0;
uint8_t beep_times = 0;
float y;
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

    if ((RxHeader.ExtId == 0x02010101U) && (RxHeader.DLC == 2U)) // 获取从板发送的报文，数据为正弦值的float数据
    {
        breathe_is_on = 1;
        buzzer_is_on = 0;
        memcpy(&y, RxData, sizeof(float));
        Sine_Wave();
    }

    else if ((RxHeader.ExtId == 0x02010102U) && (RxHeader.DLC == 1U)) // 获取CANABLE的报文，实现蜂鸣器定次数响应
    {
        beep_times = RxData[0];
        breathe_is_on = 0;
        buzzer_is_on = 1;
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