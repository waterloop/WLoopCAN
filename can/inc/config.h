#pragma once

#include "can_frame.h"

#ifdef MASTER_BMS
#include "stm32f4xx_hal.h"
#endif

#ifdef MOTOR_CONTROLLER
#include "stm32f4xx_hal.h"
#endif

#ifdef RING_ENCODER
#include "stm32f0xx_hal.h"
#endif

#ifdef PRESSURE_SENSOR
#include "stm32f3xx_hal.h"
#endif

#ifdef LV_POWER
#include "stm32f3xx_hal.h"
#endif

#ifdef TEMP_SENSOR
#include "stm32f3xx_hal.h"
#endif

/*
Size of the Rx software fifo in bytes
*/
#define RX_BUFF_SIZE    20

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

typedef enum {
    RESTING = 0x00,
    LV_READY = 0x01,
    ARMED = 0x02,
    AUTO_PILOT = 0x03,
    BRAKING = 0x04,
    EMERGENCY_BRAKE = 0x05,
    SYSTEM_FAILURE = 0x06,
    MANUAL_OPERATION_WAITING = 0x07,
    ACCELERATING = 0x08,
    AT_SPEED = 0x09,
    DECELERATING = 0x0A
} StateID;

extern const Field STATE_ID;
extern const Field TARGET_SPEED;
extern const Field TARGET_FREQ;
extern const Field TARGET_POWER;

#ifdef MASTER_BMS

typedef enum {
    SEVERE = 0x00,
    DANGER = 0x01,
    WARNING = 0x02
} BmsSeverityCode;

typedef enum {
    BATTERY_OVERVOLTAGE_ERR = 0x00,
    BATTERY_UNDERVOLTAGAE_ERR = 0x01,
    BATTERY_OVERCURRENT_ERR = 0x02,
    BATTERY_SOC_ERR = 0x03,
    CELL_UNDERVOLTAGE_ERR = 0x04,
    CELL_OVERVOLTAGE_ERR = 0x05,
    CELL_TEMPERATURE_ERR = 0x06,
    BUCK_TEMPERATURE_ERR = 0x07
} BmsErrorCode;

extern const Field BMS_SEVERITY_CODE;
extern const Field BMS_ERROR_CODE;
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
extern const Field MC_POD_SPEED;
extern const Field MOTOR_CURRENT;
extern const Field BATTERY_CURRENT;
extern const Field BATTERY_VOLTAGE;
extern const Field MC_STATE_CHANGE_ACK_NACK;

#endif

#ifdef RING_ENCODER
extern const Field RE_POD_SPEED;
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
