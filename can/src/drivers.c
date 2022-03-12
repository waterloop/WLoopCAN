#include <stdio.h>
#include "exceptions.h"
#include "circ_queue.h"
#include "can_frame.h"
#include "config.h"
#include "drivers.h"

// Number of allowable missed hearbeats before an error flag occurrs
#define MAX_HEARTBEAT_MEASURE 5

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CAN_HandleTypeDef *CAN_HANDLE;

CAN_TxHeaderTypeDef TX_HDR = {
    .StdId = 0x0000,                // not used
    .ExtId = 0x00000000,            // write correct arb_id before a frame is sent
    .IDE = CAN_ID_STD,              // use 11 bit IDs
    .RTR = CAN_RTR_DATA,            // send data frames
    .DLC = 8,                       // send 8-byte payloads
    .TransmitGlobalTime = DISABLE   // don't send timestamps
};
uint32_t TX_MAILBOX;

CAN_TxHeaderTypeDef BUS_TEST_TX_HDR = {
    .StdId = 0x0000,                // not used
    .ExtId = 0x00000000,            // write correct arb_id before a frame is sent
    .IDE = CAN_ID_STD,              // use 11 bit IDs
    .RTR = CAN_RTR_DATA,            // send data frames
    .DLC = 8,                       // send 8-byte payloads
    .TransmitGlobalTime = DISABLE   // don't send timestamps
};
uint32_t BUS_TEST_TX_MAILBOX;

Queue RX_QUEUE;
CAN_RxHeaderTypeDef RX_HDR;
uint8_t RX_BUFF[8];

uint8_t RELAY_HEARTBEAT_ERROR_FLAG;
TIM_HandleTypeDef *HEARTBEAT_TIMER;
uint8_t RELAY_HEARTBEAT_COUNTER;
uint8_t RELAY_HEARTBEAT_RX;

struct _filter_bank FILTER_BANK_MAP[MAX_NUM_FILTER_BANKS];
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RX_HDR, RX_BUFF) != HAL_OK) {
        CANBus_error_handler();
    }
    // Bus test req
    if (~(RX_HDR.StdID | ~BUS_TEST_REQ_MASK) == 0) {
        BUS_TEST_TX_HDR.StdId = BUS_TEST_RESP_BASE | (RX_HDR.StdID - BUS_TEST_REQ_BASE);
        uint8_t payload[8] = {0};

        if(HAL_CAN_AddTxMessage(CAN_HANDLE, &BUS_TEST_TX_HDR, payload, &BUS_TEST_TX_MAILBOX) != HAL_OK) {
            CANBus_error_handler();
        }
    } else {
        if (RX_HDR.StdId == STATE_CHANGE_REQ) {
            RELAY_HEARTBEAT_COUNTER = 0;
        } 
        CANFrame rx_frame = CANFrame_init(RX_HDR.StdId);
        for (uint8_t i = 0; i < 8; i++) {
            rx_frame.pld[i] = RX_BUFF[i];
        }
        Queue_put(&RX_QUEUE, rx_frame);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (HEARTBEAT_TIMER == htim) {
        RELAY_HEARTBEAT_COUNTER++;
        if (RELAY_HEARTBEAT_COUNTER > MAX_HEARTBEAT_MEASURE) {
            RELAY_HEARTBEAT_ERROR_FLAG = 1;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
HAL_StatusTypeDef CANBus_init(CAN_HandleTypeDef* hcan, TIM_HandleTypeDef* htim) {
    // initialize global variables
    CAN_HANDLE = hcan;
    RX_QUEUE = Queue_init();
    for (uint8_t i = 0; i < MAX_NUM_FILTER_BANKS; i++) {
        FILTER_BANK_MAP[i].filter_typedef.FilterActivation = CAN_FILTER_DISABLE;
        FILTER_BANK_MAP[i].filter_typedef.FilterBank = i;
        FILTER_BANK_MAP[i].id = -1;
    }

    // start the CAN peripheral
    int8_t status;
    status = HAL_CAN_Start(CAN_HANDLE);
    if (status != HAL_OK) { return status; }

    status = HAL_CAN_ActivateNotification(CAN_HANDLE, CAN_IT_RX_FIFO0_MSG_PENDING);
    if (status != HAL_OK) { return status; }

    // Initialize the RPi heartbeat monitoring
    RELAY_HEARTBEAT_ERROR_FLAG = 0;
    RELAY_HEARTBEAT_COUNTER = 0;
    RELAY_HEARTBEAT_RX = 0;

    HEARTBEAT_TIMER = htim;

    return HAL_OK;
}

HAL_StatusTypeDef CANBus_subscribe(uint16_t msg) {
    return CANBus_subscribe_mask(msg, 0xFFFF);
}

/**
  * @param msg: 11 bit CAN message id
  * @param mask: 11 bit mask (1 for match 0 for dont care)
  */
HAL_StatusTypeDef CANBus_subscribe_mask(uint16_t msg, uint16_t mask) {
    // find the first unused filter
    int8_t bank_num = -1;
    for (uint8_t i = 0; i < MAX_NUM_FILTER_BANKS; i++) {
        if (FILTER_BANK_MAP[i].filter_typedef.FilterActivation == CAN_FILTER_DISABLE) {
            bank_num = i;
            break;
        }
    }

    if (bank_num == -1) {
        printf("Error: all filter banks are currently in use\r\n");
        return HAL_ERROR;
    }

    uint16_t std_id = msg & 0x7ff;

    CAN_FilterTypeDef filter = {
        .FilterActivation = CAN_FILTER_ENABLE,
        .FilterBank = bank_num,
        .FilterFIFOAssignment = CAN_RX_FIFO0,
        .SlaveStartFilterBank = MAX_NUM_FILTER_BANKS - 1,

        .FilterMode = CAN_FILTERMODE_IDMASK,
        .FilterScale = CAN_FILTERSCALE_32BIT,

        .FilterIdHigh = std_id << 5,
        .FilterIdLow = 0,

        .FilterMaskIdHigh = mask << 5,
        .FilterMaskIdLow = 0
    };
    int8_t status = HAL_CAN_ConfigFilter(CAN_HANDLE, &filter);

    if (status == HAL_OK) {
        FILTER_BANK_MAP[bank_num].filter_typedef = filter;
        FILTER_BANK_MAP[bank_num].id = msg;
    }
    return status;
}
HAL_StatusTypeDef CANBus_unsubscribe(uint16_t msg) {
    // find the filter bank associated with the given msg
    int8_t bank_num = -1;
    for (uint8_t i = 0; i < MAX_NUM_FILTER_BANKS; i++) {
        if (FILTER_BANK_MAP[i].id == msg) {
            bank_num = i;
        }
    }

    if (bank_num == -1) {
        printf("Error: not currently subscribed to the given msg...\r\n");
        return HAL_ERROR;
    }

    CAN_FilterTypeDef filter = {
        .FilterActivation = CAN_FILTER_DISABLE,
        .FilterBank = bank_num,
    };
    int8_t status = HAL_CAN_ConfigFilter(CAN_HANDLE, &filter);

    if (status == HAL_OK) {
        FILTER_BANK_MAP[bank_num].filter_typedef = filter;
        FILTER_BANK_MAP[bank_num].id = -1;
    }
    return status;
}
HAL_StatusTypeDef CANBus_subscribe_all() {
    // find the first unused filter
    int8_t bank_num = -1;
    for (uint8_t i = 0; i < MAX_NUM_FILTER_BANKS; i++) {
        if (FILTER_BANK_MAP[i].filter_typedef.FilterActivation == CAN_FILTER_DISABLE) {
            bank_num = i;
            break;
        }
    }

    if (bank_num == -1) {
        printf("Error: all filter banks are currently in use\r\n");
        return HAL_ERROR;
    }

    CAN_FilterTypeDef filter = {
        .FilterActivation = CAN_FILTER_ENABLE,
        .FilterBank = bank_num,
        .FilterFIFOAssignment = CAN_RX_FIFO0,
        .SlaveStartFilterBank = MAX_NUM_FILTER_BANKS - 1,

        .FilterMode = CAN_FILTERMODE_IDMASK,
        .FilterScale = CAN_FILTERSCALE_32BIT,

        .FilterIdHigh = 0,
        .FilterIdLow = 0,
        .FilterMaskIdHigh = 0,
        .FilterMaskIdLow = 0
    };
    int8_t status = HAL_CAN_ConfigFilter(CAN_HANDLE, &filter);

    if (status == HAL_OK) {
        FILTER_BANK_MAP[bank_num].filter_typedef = filter;
        FILTER_BANK_MAP[bank_num].id = 0xffffffff;
    }
    return status;
}


HAL_StatusTypeDef CANBus_put_frame(CANFrame* frame) {
    TX_HDR.StdId = frame->id;

    int8_t status = HAL_CAN_AddTxMessage(CAN_HANDLE, &TX_HDR, frame->pld, &TX_MAILBOX);
    while (HAL_CAN_IsTxMessagePending(CAN_HANDLE, TX_MAILBOX)) { asm("NOP"); }
    return status;
}
CANFrame CANBus_get_frame() {
    return Queue_get(&RX_QUEUE);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
