#pragma once

#include <stdint.h>
#include <stddef.h>

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

uint32_t CANFrame_get_field(CANFrame* self, Field field);
int8_t CANFrame_set_field(CANFrame* self, Field field, uint32_t bytes);

void CANFrame_print(CANFrame* self);
//////////////////////////////////////////////////////////////////////////

