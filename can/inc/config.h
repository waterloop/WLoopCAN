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
Fields present in self doc:
    - https://docs.google.com/spreadsheets/d/18rGH__yyJPf3jil74yTlVyFFqCOyuNzP3DCFmmIWWbo/edit#gid=0
*/

#define STATE_CHANGE_REQ 0x000U
extern const Field STATE_ID;
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

#define MANUAL_CONTROL_1 0x006U
extern const Field TARGET_SPEED;
extern const Field TARGET_FREQ;

#define MANUAL_CONTROL_2 0x007U
extern const Field TARGET_POWER;

#define MANUAL_CONTROL_3 0x008U
extern const Field SET_TEMPERATURE_LIMIT;
extern const Field SET_CURRENT_LIMIT;

#define BUS_TEST_REQ 0x7FEU
extern const Field DEVICE_ID;
typedef enum {
    RASPBERRY_PI = 0x00,
    MASTER_BMS = 0x01,
    MOTOR_CONTROLLER = 0x02,
    TEMPERATURE_SENSOR = 0x03,
    PRESSURE_SENSOR = 0x04,
    RING_ENCODER = 0x05,
    LV_POWER = 0x06
} DeviceID; 

#ifdef MASTER_BMS
#define BMS_FAULT_REPORT 0x00A
extern const Field BMS_SEVERITY_CODE;
extern const Field BMS_ERROR_CODE;
typedef enum {
    SEVERE = 0x00,
    DANGER = 0x01,
    WARNING = 0x02
} BmsSeverityCode;
typedef enum {
    BATTERY_OVERVOLTAGE_ERR = 0x00,
    BATTERY_UNDERVOLTAGE_ERR = 0x01,
    BATTERY_OVERCURRENT_ERR = 0x02,
    BATTERY_SOC_ERR = 0x03,
    CELL_UNDERVOLTAGE_ERR = 0x04,
    CELL_OVERVOLTAGE_ERR = 0x05,
    CELL_TEMPERATURE_ERR = 0x06,
    BUCK_TEMPERATURE_ERR = 0x07
} BmsErrorCode;

#define BMS_STATE_CHANGE_ACK_NACK 0x00BU
extern const Field STATE_CHANGE_ACK_ID;
extern const Field STATE_CHANGE_ACK;

#define BMS_HEALTH_CHECK 0x001U
extern const Field BATTERY_PACK_CURRENT;
extern const Field CELL_TEMPERATURE;

#define BMS_DATA_1 0x00CU
extern const Field BATTERY_PACK_VOLTAGE;
extern const Field STATE_OF_CHARGE;

#define BMS_DATA_2 0x00DU
extern const Field BUCK_TEMPERATURE;
extern const Field BMS_CURRENT;

#define BMS_DATA_3 0x00EU
extern const Field MC_CAP_VOLTAGE;

#endif

#ifdef MOTOR_CONTROLLER
#define MOTOR_CONTROLLER_FAULT_REPORT 0x014
extern const Field MOTOR_CONTROLLER_SEVERITY_CODE;
extern const Field MOTOR_CONTROLLER_ERROR_CODE;

#define MOTOR_CONTROLLER_HEALTH_CHECK 0x002U
extern const Field IGBT_TEMPERATURE;
extern const Field MOTOR_VOLTAGE;

#define MOTOR_CONTROLLER_DATA_1 0x016U
extern const Field MC_POD_SPEED;
extern const Field MOTOR_CURRENT;

#define MOTOR_CONTROLLER_DATA_2 0x017U
extern const Field BATTERY_CURRENT;
extern const Field BATTERY_VOLTAGE;

#define MOTOR_CONTROLLER_STATE_CHANGE_ACK_NACK
extern const Field STATE_ID_ACK_NACK;

#endif

#ifdef RING_ENCODER
#define RING_ENCODER_DATA 0x01FU
extern const Field RE_POD_SPEED;
#endif

#ifdef PRESSURE_SENSOR
#define PRESSURE_SENSOR_HIGH 0x020U
extern const Field PRESSURE_HIGH;

#define PRESSURE_SENSOR_LOW_1 0x021U
extern const Field PRESSURE_LOW_1;

#define PRESSURE_SENSOR_LOW_2 0x022U
extern const Field PRESSURE_LOW_2;
#endif

#ifdef LV_POWER
#define CURRENT_5V_DATA 0x030U
extern const Field CURRENT_5V;

#define CURRENT_12V_DATA 0x031U
extern const Field CURRENT_12V;

#define CURRENT_24V_DATA 0x032U
extern const Field CURRENT_24V;
#endif

#ifdef TEMP_SENSOR
#endif
