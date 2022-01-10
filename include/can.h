#pragma once

#ifdef __cplusplus
extern "c" {
#endif

#include "../can/inc/can_frame.h"
#include "../can/inc/circ_queue.h"
#include "../can/inc/config.h"
#include "../can/inc/drivers.h"
#include "../can/inc/helpers.h"

#ifdef DEBUG
    #include "../tests/inc/echo.h"
#endif

#ifdef __cplusplus
}
#endif
