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

    CANFrame asdf = CANFrame_init(BATTERY_PACK_CURRENT.id);
    CANFrame_set_field(&asdf, BATTERY_PACK_CURRENT, FLOAT_TO_UINT(420.69));
    CANFrame_set_field(&asdf, CELL_TEMPERATURE, FLOAT_TO_UINT(69.420));

    while (1) {
        if (CANBus_put_frame(&asdf) != HAL_OK) { CANBus_error_handler();  }

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


void CAN_test(CAN_HandleTypeDef hcan) {
    if ( CANBus_init(&hcan) != HAL_OK) { CANBus_error_handler(); }

    if (CANBus_subscribe_all() != HAL_OK) { CANBus_error_handler(); };

//    CANFrame tx_frame = CANFrame_init(BATTERY_PACK_CURRENT.id);
//    CANFrame_set_field(&tx_frame, BATTERY_PACK_CURRENT, FLOAT_TO_UINT(4.20));
//    CANFrame_set_field(&tx_frame, CELL_TEMPERATURE, FLOAT_TO_UINT(69.420));
//
//    HAL_Delay(1000);
//    printf("starting test...\r\n");
//    printf("\r\n");
//    while (1) {
//        {
//            char str[10];
//            input("Press enter to send a CAN Frame: ", str);
//        }
//        if (CANBus_put_frame(&tx_frame) != HAL_OK) { Error_Handler(); }
//        printf("CAN Frame has been sent...\r\n\r\n");
//
//        while (!Queue_empty(&RX_QUEUE)) {
//            printf("received frame : ");
//            CANFrame rx_frame = CANBus_get_frame();
//            CANFrame_print(&rx_frame);
//        }

        // if (!Queue_empty(&RX_QUEUE)) {
        //     CANFrame rx_frame = CANBus_get_frame();
        //     float batt_curr = UINT_TO_FLOAT(CANFrame_get_field(&rx_frame, BATTERY_PACK_CURRENT));
        //     float cell_temp = UINT_TO_FLOAT(CANFrame_get_field(&rx_frame, CELL_TEMPERATURE));
        //     printf("batt_curr = %.4f\r\n", batt_curr);
        //     printf("cell_temp = %.4f\r\n", cell_temp);
        // }
        // HAL_Delay(500);
//    }
}

