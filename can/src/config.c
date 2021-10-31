#include "can_frame.h"
#include "config.h"

/*
Fields present in this doc:
    - https://docs.google.com/spreadsheets/d/18rGH__yyJPf3jil74yTlVyFFqCOyuNzP3DCFmmIWWbo/edit#gid=0

Start and stop indices (stop indices are +1 the actual index)
*/
const Field STATE_ID            = {0x000, 0, 1};
const Field TARGET_SPEED        = {0x006, 0, 4};
const Field TARGET_FREQUENCY    = {0x006, 4, 8};
const Field TARGET_POWER        = {0x007, 0, 4};

#ifdef MASTER_BMS
    const Field BMS_FAULT_REPORT            = {0x00A, 0, 0};
    const Field BMS_STATE_CHANGE_ACK_NACK   = {0x00B, 0, 1};
    const Field BATTERY_PACK_CURRENT        = {0x001, 0, 4};
    const Field CELL_TEMPERATURE            = {0x001, 4, 8};
    const Field BATTERY_PACK_VOLTAGE        = {0x00C, 0, 4};
    const Field STATE_OF_CHARGE             = {0x00C, 4, 8};
    const Field BUCK_TEMPERATURE            = {0x00D, 0, 4};
    const Field BMS_CURRENT                 = {0x00D, 4, 8};
    const Field MC_CAP_VOLTAGE              = {0x00E, 0, 4};
#endif

#ifdef MOTOR_CONTROLLER
    const Field MC_FAULT_REPORT             = {0x014, 0, 0};
    const Field MC_STATE_CHANGE_ACK_NACK    = {0x015, 0, 1};
    const Field IGBT_TEMPERATURE            = {0x002, 0, 4};
    const Field MOTOR_VOLTAGE               = {0x002, 4, 8};
    const Field POD_SPEED                   = {0x016, 0, 4};
    const Field MOTOR_CURRENT               = {0x016, 4, 8};
    const Field BATTERY_CURRENT             = {0x017, 0, 4};
    const Field BATTERY_VOLTAGE             = {0x017, 4, 8};
#endif

#ifdef RING_ENCODER
    const Field POD_SPEED = {0x01F, 0, 4};
#endif

#ifdef PRESSURE_SENSOR
#endif

#ifdef LV_POWER
    const Field CURRENT_5V  = {0x030, 0, 4};
    const Field CURRENT_12V = {0x031, 0, 4};
    const Field CURRENT_24V = {0x032, 0, 4};
#endif

#ifdef TEMP_SENSOR
#endif
