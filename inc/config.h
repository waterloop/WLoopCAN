#pragma once

#ifdef MASTER_BMS
#include "stm32f4xx_hal.h"
#endif

#ifdef MOTOR_CONTROLLER
#include "stm32f4xx_hal.h"
#endif

#ifdef RING_ENCODER
#endif

#ifdef PRESSURE_SENSOR
#endif

#ifdef LV_POWER
#endif

#ifdef TEMP_SENSOR
#endif

#include "can_frame.h"

/*
Size of the Rx software fifo in bytes
*/
#define RX_BUFF_SIZE    100

/*
Number of CAN filter banks
*/
#ifdef MASTER_BMS
#define MAX_NUM_FILTER_BANKS    14
#endif

#ifdef MOTOR_CONTROLLER
#define MAX_NUM_FILTER_BANKS    14
#endif

#ifdef RING_ENCODER
#define MAX_NUM_FILTER_BANKS    14
#endif

#ifdef PRESSURE_SENSOR
#define MAX_NUM_FILTER_BANKS    14
#endif

#ifdef LV_POWER
#define MAX_NUM_FILTER_BANKS    14
#endif

#ifdef TEMP_SENSOR
#define MAX_NUM_FILTER_BANKS    14
#endif

/*
Fields present in this doc:
    - https://docs.google.com/spreadsheets/d/18rGH__yyJPf3jil74yTlVyFFqCOyuNzP3DCFmmIWWbo/edit#gid=0
*/

extern const Field STATE_ID;
extern const Field TARGET_SPEED;
extern const Field TARGET_FREQ;
extern const Field TARGET_POWER;

#ifdef MASTER_BMS
    extern const Field BMS_STATE_CHANGE_ACK_NACK;
    extern const Field BATTERY_PACK_CURRENT;
    extern const Field CELL_TEMPERATURE;
    extern const Field BATTERY_PACK_VOLTAGE;
    extern const Field STATE_OF_CHARGE;
    extern const Field BUCK_TEMPERATURE;
    extern const Field BMS_CURRENT;
    extern const Field MC_CAP_VOLTAGE;
#endif

#ifdef MOTOR_CONTROLLER
    extern const Field IGBT_TEMPERATURE;
    extern const Field MOTOR_VOLTAGE;
    extern const Field POD_SPEED;
    extern const Field MOTOR_CURRENT;
    extern const Field BATTERY_CURRENT;
    extern const Field BATTERY_VOLTAGE;
    extern const Field MC_STATE_CHANGE_ACK_NACK;
#endif

#ifdef RING_ENCODER
    const Field POD_SPEED;
#endif

#ifdef PRESSURE_SENSOR
#endif

#ifdef LV_POWER
    extern const Field CURRENT_5V;
    extern const Field CURRENT_12V;
    extern const Field CURRENT_24V;
#endif

#ifdef TEMP_SENSOR
#endif
