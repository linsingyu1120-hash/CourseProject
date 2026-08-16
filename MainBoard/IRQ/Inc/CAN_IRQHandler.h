#ifndef CAN_IRQHANDLER_H
#define CAN_IRQHANDLER_H

#include "main.h"
#include "can.h"

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void CAN_Task(void);

HAL_StatusTypeDef CAN_Send_Message(uint32_t StdId, uint8_t DLC, uint8_t *TxData);

extern float y;

#endif