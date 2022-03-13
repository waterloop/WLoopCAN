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
extern CAN_HandleTypeDef *CAN_HANDLE;

// General TX Header
extern CAN_TxHeaderTypeDef TX_HDR;
extern uint32_t TX_MAILBOX;

// Bus Test TX Header
extern CAN_TxHeaderTypeDef BUS_TEST_TX_HDR;
extern uint32_t BUS_TEST_TX_MAILBOX;

// Receive message Queue
extern Queue RX_QUEUE;
extern CAN_RxHeaderTypeDef RX_HDR;
extern uint8_t RX_BUFF[8];

// Relay board heartbeat monitoring
extern uint8_t RELAY_HEARTBEAT_ERROR_FLAG;
extern TIM_HandleTypeDef *HEARTBEAT_TIMER;
extern uint8_t RELAY_HEARTBEAT_COUNTER;

extern struct _filter_bank FILTER_BANK_MAP[MAX_NUM_FILTER_BANKS];
////////////////////////////////////////////////////////////////////////////////

void CANBus_timer_isr(TIM_HandleTypeDef* htim);

////////////////////////////////////////////////////////////////////////////////

HAL_StatusTypeDef CANBus_init(CAN_HandleTypeDef* hcan, TIM_HandleTypeDef* htim);

HAL_StatusTypeDef CANBus_subscribe(uint16_t msg);
HAL_StatusTypeDef CANBus_subscribe_mask(uint16_t msg, uint16_t mask);
HAL_StatusTypeDef CANBus_unsubscribe(uint16_t msg);
HAL_StatusTypeDef CANBus_subscribe_all();

HAL_StatusTypeDef CANBus_put_frame(CANFrame* frame); 
CANFrame CANBus_get_frame();

