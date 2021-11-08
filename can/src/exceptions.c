#include "exceptions.h"

void CANBus_error_handler() {
    while (1) { asm("NOP"); }
}
