#include "helpers.h"

float UINT_TO_FLOAT(uint32_t ui) {
    union _byteshare temp;
    temp.ui = ui;
    return temp.f;
}
uint32_t FLOAT_TO_UINT(float f) {
    union _byteshare temp;
    temp.f = f;
    return temp.ui;
}
