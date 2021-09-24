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

uint8_t Queue_empty(Queue* this) {
    return this->len == 0;
}

void Queue_put(Queue* this, CANFrame val) {
    if ( !(this->len == RX_BUFF_SIZE) ) {
        // regular insert condition
        if (Queue_empty(this)) {
            this->_arr[this->_head] = val;
        }
        else {
            _INC_TAIL(this);
            this->_arr[this->_tail] = val;
        }
        this->len += 1;
    }
    else {
        // overwrite condition
        this->_arr[this->_head] = val;
        _INC_HEAD(this);
        _INC_TAIL(this);
    }
}
CANFrame Queue_get(Queue* this) {
    CANFrame ret = this->_arr[this->_head];
    _INC_HEAD(this);
    if (!Queue_empty(this)) {
        this->len -= 1;
    }
    return ret;
}

void Queue_print(Queue* this) {
    printf("[");
    for (size_t i = 0; i < (RX_BUFF_SIZE - 1); i++) {
        printf("%ld, ", this->_arr[i].id);
    }
    printf(
        "%ld], head = %ld, tail = %ld, len = %d\n",
        this->_arr[RX_BUFF_SIZE - 1].id, this->_arr[this->_head].id, this->_arr[this->_tail].id, this->len
    );
}