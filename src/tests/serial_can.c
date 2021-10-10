#include "main.h"
#include "can_frame.h"
#include "drivers.h"
#include "tests/serial_can.h"

void input(char* msg, char* input_buff) {
    printf(msg);
    scanf("%s", input_buff);
    printf("\r\n");
}

void CAN_test() {
    if ( CANBus_init(&hcan1) != HAL_OK) { Error_Handler(); }

    hcan1.Instance->MCR &= ~(1 << 16);

    if (CANBus_subscribe(BATTERY_PACK_CURRENT) != HAL_OK) { Error_Handler(); };

    CANFrame tx_frame = CANFrame_init(BATTERY_PACK_CURRENT.id);
    CANFrame_set_field(&tx_frame, BATTERY_PACK_CURRENT, FLOAT_TO_UINT(4.20));
    CANFrame_set_field(&tx_frame, CELL_TEMPERATURE, FLOAT_TO_UINT(69.420));

    HAL_Delay(5000);
    printf("starting test...\r\n");
    printf("\r\n");
    while (1) {
        {
            char str[10];
            input("Press enter to send a CAN Frame: ", str);
        }
        if (CANBus_put_frame(&tx_frame) != HAL_OK) { Error_Handler(); }
        printf("CAN Frame has been sent...\r\n\r\n");

        while (!Queue_empty(&RX_QUEUE)) {
            printf("received frame : ");
            CANFrame rx_frame = CANBus_get_frame();
            CANFrame_print(&rx_frame);
        }

        // if (!Queue_empty(&RX_QUEUE)) {
        //     CANFrame rx_frame = CANBus_get_frame();
        //     float batt_curr = UINT_TO_FLOAT(CANFrame_get_field(&rx_frame, BATTERY_PACK_CURRENT));
        //     float cell_temp = UINT_TO_FLOAT(CANFrame_get_field(&rx_frame, CELL_TEMPERATURE));
        //     printf("batt_curr = %.4f\r\n", batt_curr);
        //     printf("cell_temp = %.4f\r\n", cell_temp);
        // }
        // HAL_Delay(500);
    }
}

