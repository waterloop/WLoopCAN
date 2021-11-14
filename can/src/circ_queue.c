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
    /*
    This functions is called in ISR, so it should be
    as fast as possible. As such, it is written to be
    branchless.

    IDK how much of an impact this will really have tho??
    The pipeline is probably flushed on IRQ, but its probably
    still good to have this branchless?? Not sure.

    The below code is meant to be a brancless version of this:

    if ( !(this->len == RX_BUFF_SIZE) ) {
        // regular insert condition
        if (this->len == 0) {
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
        _INC_HEAD(this)
        _INC_TAIL(this)
    }
    */
    uint8_t not_full = !(this->len == RX_BUFF_SIZE);
    uint8_t empty = (this->len == 0);

    size_t incremeneted_head = _INC_HEAD(this);
    size_t incremeneted_tail = _INC_TAIL(this);

    /*
    Use 'this->_head' as the index if:
        1. The queue is not full AND its empty, OR
        2. The queue is full

    Use the incremented tail as the index if:
        1. The queue is not full AND the queue is not empty
    */
    size_t indx = this->_head*(not_full*empty + (!not_full)) +
                  incremeneted_tail*not_full*(!empty);

    this->_arr[indx] = val;

    this->len += not_full;

    // The head shoud be incremented if the queue is full
    this->_head = this->_head*not_full + incremeneted_head*(!not_full);

    /*
    The tail should be incremented if:
        1. the queue is not full AND not empty, OR
        2. the queue is full
    */
    this->_tail = this->_tail*not_full*empty +
                  incremeneted_tail*(not_full*(!empty) + (!not_full));
}
CANFrame Queue_get(Queue* this) {
    if (this->len == 0) {
        CANFrame ret = {
            .id = 0xffffffff,
            .pld = {0xff}
        };
        return ret;
    }
    else {
        CANFrame ret = this->_arr[this->_head];
        this->_head = _INC_HEAD(this);

        /*
        Branchless way of doing:
            if (this->len != 0) { this->len -= 1; }
        */
        uint8_t not_empty = (this->len != 0);
        this->len -= not_empty;

        return ret;
    }
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
