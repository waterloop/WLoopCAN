#pragma once

#include <stdint.h>

union _byteshare {
    uint32_t ui;
    float f;
};

float UINT_TO_FLOAT(uint32_t ui);
uint32_t FLOAT_TO_UINT(float f);

