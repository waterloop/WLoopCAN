#include <stdio.h>
#include "config.h"
#include "circ_queue.h"

Queue Queue_init() {
    Queue ret = {
        .len = 0,
        ._arr = { {0} },
        ._head = 0,
        ._tail = 0
    };
    return ret;
}

uint8_t Queue_empty(Queue* self) {
    return self->len == 0;
}

void Queue_put(Queue* self, CANFrame val) {
    if ( !(self->len == RX_BUFF_SIZE) ) {
        // regular insert condition
        if (Queue_empty(self)) {
            self->_arr[self->_head] = val;
        }
        else {
            _INC_TAIL(self);
            self->_arr[self->_tail] = val;
        }
        self->len += 1;
    }
    else {
        // overwrite condition
        self->_arr[self->_head] = val;
        _INC_HEAD(self);
        _INC_TAIL(self);
    }
}
CANFrame Queue_get(Queue* self) {
    if (self->len == 0) {
        CANFrame ret = {
            .id = 0xffffffff,
            .pld = {0xff}
        };
        return ret;
    }
    else {
        CANFrame ret = self->_arr[self->_head];
        _INC_HEAD(self);
        if (!Queue_empty(self)) {
            self->len -= 1;
        }
        return ret;
    }
}

void Queue_print(Queue* self) {
    printf("[");
    for (size_t i = 0; i < (RX_BUFF_SIZE - 1); i++) {
        printf("%ld, ", self->_arr[i].id);
    }
    printf(
        "%ld], head = %ld, tail = %ld, len = %d\n",
        self->_arr[RX_BUFF_SIZE - 1].id, self->_arr[self->_head].id, self->_arr[self->_tail].id, self->len
    );
}
