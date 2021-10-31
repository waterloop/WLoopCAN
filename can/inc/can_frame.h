#pragma once

#include <stdint.h>
#include <stddef.h>


//////////////////////////////////////////////////////////////////////////
typedef enum {
    RESTING,
    LV_READY,
    ARMED,
    AUTO_PILOT,
    BRAKING,
    EMERGENCY_BRAKE,
    SYSTEM_FAILURE,
    MANUAL_OPERATION_WAITING,
    ACCELERATING,
    AT_SPEED,
    DECELERATING
} StateID;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
typedef struct {
    uint32_t id;        // arbitration id of field
    uint8_t start;      // start index
    uint8_t stop;       // stop index + 1 ==> (stop - start = length)
} Field;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
#define MAX_CAN_PAYLOAD_BTYES    8

typedef struct {
    uint32_t id;
    uint8_t pld[MAX_CAN_PAYLOAD_BTYES];
} CANFrame;

CANFrame CANFrame_init(uint32_t id);

uint32_t CANFrame_get_field(CANFrame* this, Field field);
int8_t CANFrame_set_field(CANFrame* this, Field field, uint32_t bytes);

void CANFrame_print(CANFrame* this);
//////////////////////////////////////////////////////////////////////////

