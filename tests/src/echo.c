#include <stdio.h>
#include "exceptions.h"
#include "can_frame.h"
#include "drivers.h"
#include "helpers.h"
#include "echo.h"

void input(char* msg, char* input_buff) {
    printf(msg);
    scanf("%s", input_buff);
    printf("\r\n");
}

void echo(CAN_HandleTypeDef* hcan) {
    if (CANBus_init(hcan) != HAL_OK) { CANBus_error_handler(); }
    if (CANBus_subscribe_all() != HAL_OK) { CANBus_error_handler(); }

    hcan->Instance->MCR = 0x60;

    while (1) {
        if (!Queue_empty(&RX_QUEUE)) {
            CANFrame rx_frame = CANBus_get_frame();
            CANFrame tx_frame = CANFrame_init(rx_frame.id);
            for (uint8_t i = 0; i < 8; i++) {
                tx_frame.pld[i] = rx_frame.pld[i];
            }
            if (CANBus_put_frame(&tx_frame) != HAL_OK) { CANBus_error_handler(); }
        }
    }

}

