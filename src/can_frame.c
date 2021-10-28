#include <stdio.h>
#include "can_frame.h"

//////////////////////////////////////////////////////////////////////////
// CANFrame Object
CANFrame CANFrame_init(uint32_t id) {
    CANFrame ret = {
        .id = id,
        .pld = {0}
    };
    return ret;
}

uint32_t CANFrame_get_field(CANFrame* this, Field field) {
    if (field.id != this->id) {
        return 0xffffffff;
    }
    uint8_t len = field.stop - field.start;
    uint32_t ret = 0;
    for (uint8_t i = 0; i < len; i++) {
        uint8_t byte = this->pld[field.start + i];
        ret |= (byte << (8*i));
    }
    return ret;
}
int8_t CANFrame_set_field(CANFrame* this, Field field, uint32_t bytes) {
    if (field.id != this->id) {
        return -1;
    }
    uint8_t len = field.stop - field.start;
    for (uint8_t i = 0; i < len; i++) {
        this->pld[i + field.start] = (bytes >> (8*i)) & 0xff;
    }
    return 0;
}

void CANFrame_print(CANFrame* this) {
    printf("{\r\n");
    printf("\tid: %ld\r\n", this->id);
    printf("\t[");
    for (uint8_t i = 0; i < 7; i++) {
        printf("%d, ", this->pld[i]);
    }
    printf("%d]\r\n", this->pld[7]);
    printf("}\r\n");
}
//////////////////////////////////////////////////////////////////////////


