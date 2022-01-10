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

#define _INC_HEAD(self) {                       \
    if (self->_head == (RX_BUFF_SIZE - 1)) {    \
        self->_head = 0;                        \
    }                                           \
    else {                                      \
        self->_head += 1;                       \
    }                                           \
}
#define _INC_TAIL(self) {                       \
    if (self->_tail == (RX_BUFF_SIZE - 1)) {    \
        self->_tail = 0;                        \
    }                                           \
    else {                                      \
        self->_tail += 1;                       \
    }                                           \
}

Queue Queue_init();
uint8_t Queue_empty(Queue* self);
void Queue_put(Queue* self, CANFrame val);
CANFrame Queue_get(Queue* self);

void Queue_print(Queue* self);

