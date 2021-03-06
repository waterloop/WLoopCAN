#include "can_frame.h"
#include "config.h"

/*
Fields present in self doc:
    - https://docs.google.com/spreadsheets/d/18rGH__yyJPf3jil74yTlVyFFqCOyuNzP3DCFmmIWWbo/edit#gid=0

Start and stop indices (stop indices are +1 the actual index)
*/
const Field STATE_ID                = {STATE_CHANGE_REQ, 0, 1};
const Field TRACK_LENGTH            = {STATE_CHANGE_REQ, 1, 5};

const Field TARGET_SPEED            = {MANUAL_CONTROL_1, 0, 4};
const Field TARGET_FREQUENCY        = {MANUAL_CONTROL_1, 4, 8};

const Field TARGET_POWER            = {MANUAL_CONTROL_2, 0, 4};

const Field SET_TEMPERATURE_LIMIT   = {MANUAL_CONTROL_3, 0, 4};
const Field SET_CURRENT_LIMIT       = {MANUAL_CONTROL_3, 4, 8};

#ifdef MASTER_BMS
    const Field BMS_SEVERITY_CODE           = {BMS_FAULT_REPORT, 0, 1};
    const Field BMS_ERROR_CODE              = {BMS_FAULT_REPORT, 1, 2};

    const Field STATE_CHANGE_ACK_ID         = {BMS_STATE_CHANGE_ACK_NACK, 0, 1};
    const Field STATE_CHANGE_ACK            = {BMS_STATE_CHANGE_ACK_NACK, 1, 2};

    const Field BATTERY_PACK_CURRENT        = {BMS_HEALTH_CHECK, 0, 4};
    const Field CELL_TEMPERATURE            = {BMS_HEALTH_CHECK, 4, 8};
    const Field BATTERY_PACK_VOLTAGE        = {BMS_DATA_1, 0, 4};
    const Field STATE_OF_CHARGE             = {BMS_DATA_1, 4, 8};
    const Field BUCK_TEMPERATURE            = {BMS_DATA_2, 0, 4};
    const Field BMS_CURRENT                 = {BMS_DATA_2, 4, 8};
    const Field MC_CAP_VOLTAGE              = {BMS_DATA_3, 0, 4};
#endif

#ifdef MOTOR_CONTROLLER
    const Field MOTOR_CONTROLLER_SEVERITY_CODE      = {MOTOR_CONTROLLER_FAULT_REPORT, 0, 1};
    const Field MOTOR_CONTROLLER_ERROR_CODE         = {MOTOR_CONTROLLER_FAULT_REPORT, 1, 2};
    const Field MOTOR_CONTROLLER_PHASE_MASK         = {MOTOR_CONTROLLER_FAULT_REPORT, 2, 3};

    const Field STATE_CHANGE_ACK_ID                 = {MOTOR_CONTROLLER_STATE_CHANGE_ACK_NACK, 0, 1};
    const Field STATE_CHANGE_ACK                    = {MOTOR_CONTROLLER_STATE_CHANGE_ACK_NACK, 1, 2};
    
    const Field FET_TEMPERATURE                     = {MOTOR_CONTROLLER_HEALTH_CHECK, 0, 4};
    const Field MOTOR_VOLTAGE                       = {MOTOR_CONTROLLER_HEALTH_CHECK, 4, 8};

    const Field MC_POD_SPEED                        = {MOTOR_CONTROLLER_DATA_1, 0, 4};
    const Field MC_POD_ACCELERATION                 = {MOTOR_CONTROLLER_DATA_1, 4, 8};

    const Field PHASE_A_CURRENT                     = {MOTOR_CONTROLLER_PHASE_A_STATS, 0, 4};
    const Field PHASE_A_VOLTAGE                     = {MOTOR_CONTROLLER_PHASE_A_STATS, 4, 8};
    const Field PHASE_B_CURRENT                     = {MOTOR_CONTROLLER_PHASE_B_STATS, 0, 4};
    const Field PHASE_B_VOLTAGE                     = {MOTOR_CONTROLLER_PHASE_B_STATS, 4, 8};
    const Field PHASE_C_CURRENT                     = {MOTOR_CONTROLLER_PHASE_C_STATS, 0, 4};
    const Field PHASE_C_VOLTAGE                     = {MOTOR_CONTROLLER_PHASE_C_STATS, 4, 8};
#endif

#if (defined(RING_ENCODER) || defined(MOTOR_CONTROLLER))
    const Field RE_POD_SPEED = {RING_ENCODER_DATA, 0, 4};
#endif

#ifdef PRESSURE_SENSOR
    const Field PRESSURE_HIGH  = {PRESSURE_SENSOR_HIGH, 0, 4};
    const Field PRESSURE_LOW_1 = {PRESSURE_SENSOR_LOW_1, 0, 4};
    const Field PRESSURE_LOW_2 = {PRESSURE_SENSOR_LOW_2, 0, 4};
    
    const Field PRESSURE_SENSOR_STATE_CHANGE_ACK_ID         = {PRESSURE_SENSOR_STATE_CHANGE_ACK_NACK, 0, 1};
    const Field PRESSURE_SENSOR_STATE_CHANGE_ACK            = {PRESSURE_SENSOR_STATE_CHANGE_ACK_NACK, 1, 2};
#endif

#ifdef LV_POWER
    const Field CURRENT_5V  = {CURRENT_5V_DATA, 0, 4};
    const Field CURRENT_12V = {CURRENT_12V_DATA, 0, 4};
    const Field CURRENT_24V = {CURRENT_24V_DATA, 0, 4};
#endif

#ifdef TEMP_SENSOR
    const Field TORCHIC_1_TEMP_1 = {TORCHIC_1, 0, 4};
    const Field TORCHIC_1_TEMP_2 = {TORCHIC_1, 4, 8};
    const Field TORCHIC_2_TEMP_1 = {TORCHIC_2, 0, 4};
    const Field TORCHIC_2_TEMP_2 = {TORCHIC_2, 4, 8};
#endif

#ifdef POD_INDICATOR_LIGHT
    const Field BMS_STATE_CHANGE_ACK_ID         = {BMS_STATE_CHANGE_ACK_NACK, 0, 1};
    const Field BMS_STATE_CHANGE_ACK            = {BMS_STATE_CHANGE_ACK_NACK, 1, 2};
    
    const Field MOTOR_CONTROLLER_STATE_CHANGE_ACK_ID = {MOTOR_CONTROLLER_STATE_CHANGE_ACK_NACK, 0, 1};
    const Field MOTOR_CONTROLLER_STATE_CHANGE_ACK = {MOTOR_CONTROLLER_STATE_CHANGE_ACK_NACK, 1, 2};
#endif
