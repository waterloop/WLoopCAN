#include <stdio.h>
#include "main.h"
#include "circ_queue.h"
#include "can_frame.h"
#include "config.h"
#include "drivers.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CAN_HandleTypeDef CAN_HANDLE;

CAN_TxHeaderTypeDef TX_HDR = {
    .StdId = 0x0000,                // not used
    .ExtId = 0x00000000,            // write correct arb_id before a frame is sent
    .IDE = CAN_ID_EXT,              // use extended ID
    .RTR = CAN_RTR_DATA,            // send data frames
    .DLC = 8,                       // send 8-byte payloads
    .TransmitGlobalTime = DISABLE   // don't send timestamps
};
uint32_t TX_MAILBOX;

Queue RX_QUEUE;
CAN_RxHeaderTypeDef RX_HDR;
uint8_t RX_BUFF[8];

struct _filter_bank FILTER_BANK_MAP[MAX_NUM_FILTER_BANKS];
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RX_HDR, RX_BUFF) != HAL_OK) {
        Error_Handler();
    }
    CANFrame rx_frame = CANFrame_init(RX_HDR.ExtId);
    for (uint8_t i = 0; i < 8; i++) {
        rx_frame.pld[i] = RX_BUFF[i];
    }
    Queue_put(&RX_QUEUE, rx_frame);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
HAL_StatusTypeDef CANBus_init(CAN_HandleTypeDef* hcan) {
    // initialize global variables
    CAN_HANDLE = *hcan;
    RX_QUEUE = Queue_init();
    for (uint8_t i = 0; i < MAX_NUM_FILTER_BANKS; i++) {
        FILTER_BANK_MAP[i].filter_typedef.FilterActivation = CAN_FILTER_DISABLE;
        FILTER_BANK_MAP[i].filter_typedef.FilterBank = i;
        FILTER_BANK_MAP[i].id = -1;
    }

    // start the CAN peripheral
    int8_t status;
    status = HAL_CAN_Start(hcan);
    if (status != HAL_OK) { return status; }
    
    status = HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
    if (status != HAL_OK) { return status; }

    // subscribe to the pod state msg
    status = CANBus_subscribe(STATE_ID);
    if (status != HAL_OK) { return status; }

    return HAL_OK;
}

HAL_StatusTypeDef CANBus_subscribe(Field field) {
    // find the first unused filter
    int8_t bank_num = -1;
    for (uint8_t i = 0; i < MAX_NUM_FILTER_BANKS; i++) {
        if (FILTER_BANK_MAP[i].filter_typedef.FilterActivation == CAN_FILTER_DISABLE) {
            bank_num = i;
        }
    }

    if (bank_num == -1) {
        printf("Error: all filter banks are currently in use\r\n");
        return HAL_ERROR;
    }

    uint16_t std_id = field.id & 0x7FF;
    uint32_t ext_id = (field.id >> 11) & 0x1ffff;

    CAN_FilterTypeDef filter = {
        .FilterActivation = CAN_FILTER_ENABLE,
        .FilterBank = bank_num,
        .FilterFIFOAssignment = CAN_RX_FIFO0,
        .FilterIdHigh = (std_id << 5) | ( (ext_id >> 13) & 0b11111 ),
        .FilterMaskIdHigh = (std_id << 5) | ( (ext_id >> 13) & 0b11111 ),
        .FilterIdLow = (ext_id & 0x1fff) << 3,
        .FilterMaskIdLow = (ext_id & 0x1fff) << 3,
        .FilterMode = CAN_FILTERMODE_IDLIST,
        .FilterScale = CAN_FILTERSCALE_32BIT,
    };
    int8_t status = HAL_CAN_ConfigFilter(&CAN_HANDLE, &filter);

    if (status == HAL_OK) {
        FILTER_BANK_MAP[bank_num].filter_typedef = filter;
        FILTER_BANK_MAP[bank_num].id = field.id;
    }
    return status;
}
HAL_StatusTypeDef CANBus_unsubscribe(Field field) {
    // find the filter bank associated with the given field
    int8_t bank_num = -1;
    for (uint8_t i = 0; i < MAX_NUM_FILTER_BANKS; i++) {
        if (FILTER_BANK_MAP[i].id == field.id) {
            bank_num = i;
        }
    }

    if (bank_num == -1) {
        printf("Error: not currently subscribed to the given field...\r\n");
        return HAL_ERROR;
    }

    CAN_FilterTypeDef filter = {
        .FilterActivation = CAN_FILTER_DISABLE,
        .FilterBank = bank_num,
    };
    int8_t status = HAL_CAN_ConfigFilter(&CAN_HANDLE, &filter);

    if (status == HAL_OK) {
        FILTER_BANK_MAP[bank_num].filter_typedef = filter;
        FILTER_BANK_MAP[bank_num].id = -1;
    }
    return status;
}

HAL_StatusTypeDef CANBus_put_frame(CANFrame* frame) {
    TX_HDR.ExtId = frame->id;
    return HAL_CAN_AddTxMessage(&CAN_HANDLE, &TX_HDR, frame->pld, &TX_MAILBOX);
}
CANFrame CANBus_get_frame() {
    return Queue_get(&RX_QUEUE);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
