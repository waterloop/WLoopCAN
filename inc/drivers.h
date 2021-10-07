#pragma once

#include <stddef.h>
#include "config.h"
#include "circ_queue.h"
#include "can_frame.h"

struct _filter_bank {
    CAN_FilterTypeDef filter_typedef;
    int32_t id;
};

////////////////////////////////////////////////////////////////////////////////
extern CAN_HandleTypeDef CAN_HANDLE;
extern CAN_TxHeaderTypeDef TX_HDR;
extern uint32_t TX_MAILBOX;

extern Queue RX_QUEUE;
extern CAN_RxHeaderTypeDef RX_HDR;
extern uint8_t RX_BUFF[8];

extern struct _filter_bank FILTER_BANK_MAP[MAX_NUM_FILTER_BANKS];
////////////////////////////////////////////////////////////////////////////////

HAL_StatusTypeDef CANBus_init(CAN_HandleTypeDef* hcan);

HAL_StatusTypeDef CANBus_subscribe(Field field);
HAL_StatusTypeDef CANBus_unsubscribe(Field field);

HAL_StatusTypeDef CANBus_put_frame(CANFrame* frame); 
CANFrame CANBus_get_frame();

