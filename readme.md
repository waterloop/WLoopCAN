# WLoop CAN Libary

A minimal implementation of a CAN library for G5. Handles sending and receiving CAN frames from the bus.

## Installation

```bash
cd /path/to/stm32_project
git submodule add "https://github.com/waterloop/WLoopCAN.git"
git submodule update --init --recursive
```

Afterwards, your project directory should resemble the following:

```
|--STM32F405RGTx
|--|--Core
|--|--|-- ...
|---WLoopCAN
|--|--inc
|--|--|-- ...
|--|--src
|--|--|-- ...
|--|--makefile
```

## Building

**Dependencies**

* `arm-none-eabi-gcc`
* `GNU Make`

The variables shown below need to be edited in `makefile`. The example below is for the G5 Master BMS.

```makefile
########################################################
# USER DEFINED VARIABLES
DEBUG = true

BOARD = MASTER_BMS
DEVICE = STM32F405RGTx
DEVICE_VARIANT = STM32F405xx
DEVICE_FAMILY = STM32F4xx

CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
########################################################
```

Once `makefile` has been appropriately edited, the library can be build by doing:

```bash
cd /path/to/wloop_can
make
```

## Linking With STM32 Project

### GNU Make

Link `./WLoopCAN/bin/wloop_can.a` with the rest of your object files, and add `-I ./WLoopCAN/inc` to your compilation flags.

### STM32CubeIDE

Open the `Project/Properties` menu, then open `C/C++ Build/Settings`.

Under `MCU GCC Compiler`, add `../../WLoopCAN/inc` to the include paths.

Under `MCU GCC Linker/Miscellaneous` add `../../WLoopCAN/bin/wloop_can.a` to additional object files.

## Usage

The following example shows how to use the library.

```c
/*
file: main.c
*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "wloop_can.h"
/* USER CODE END Includes */

int main();

int main() {
    /* USER CODE BEGIN 2 */

    ////////////////////////////////////////////////////////////////////////////////////////////
	if (CANBus_init(&hcan1) != HAL_OK) {
    	printf("Error: failed to initialize CANBus...")
        Error_Handler();
    }
    CANBus_subscribe(BATTERY_PACK_CURRENT);	// subscribe to receive battery pack current data
    ////////////////////////////////////////////////////////////////////////////////////////////

    /*
    NOTE:
        - Received frames are put into a queue in ISR. It is the responsibility
          of the user to ensure that the queue doesn't overflow (in which case,
          the last entry in the queue will be overwritten)
    */

    ////////////////////////////////////////////////////////////////////////////////////////////
    // send a frame containing the fields BATTERY_PACK_CURRENT and CELL_TEMPERATURE
    CANFrame tx_frame = CANFrame_init(BATTERY_PACK_CURRENT.id);
    CANFrame_set_field(&tx_frame, BATTERY_PACK_CURRENT, FLOAT_TO_UINT(4.20));
    CANFrame_set_field(&tx_frame, CELL_TEMPERATURE, FLOAT_TO_UINT(69.420));
    if (CANBus_put_frame(tx_frame) < 0) {
        Error_Handler();
    }
    ////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////
    // get a received frame from the sw queue
    if (Queue_empty(&RX_QUEUE)) {
        CANFrame rx_frame = CANBus_get_frame();
        if (rx_frame.id == BATTERY_PACK_CURRENT.id) {
            float batt_curr = UINT_TO_FLOAT(CANFrame_get_field(&rx_frame, BATTERY_PACK_CURRENT));
            float cell_temp = UINT_TO_FLOAT(CANFrame_get_field(&rx_frame, CELL_TEMPERATURE));
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////

    /* USER CODE END 2 */

    return 0;
}
```

