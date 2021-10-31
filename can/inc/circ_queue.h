#pragma once

#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "can_frame.h"

/*
Implementation of a circular queue
*/

typedef struct {
    size_t len;

    CANFrame _arr[RX_BUFF_SIZE];
    size_t _head;
    size_t _tail;
} Queue;

#define _INC_HEAD(this) {                       \
    if (this->_head == (RX_BUFF_SIZE - 1)) {    \
        this->_head = 0;                        \
    }                                           \
    else {                                      \
        this->_head += 1;                       \
    }                                           \
}
#define _INC_TAIL(this) {                       \
    if (this->_tail == (RX_BUFF_SIZE - 1)) {    \
        this->_tail = 0;                        \
    }                                           \
    else {                                      \
        this->_tail += 1;                       \
    }                                           \
}

Queue Queue_init();
uint8_t Queue_empty(Queue* this);
void Queue_put(Queue* this, CANFrame val);
CANFrame Queue_get(Queue* this);

void Queue_print(Queue* this);

