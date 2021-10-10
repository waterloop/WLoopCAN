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

### STM32CubeIDE

Follow the following steps to setup the build:

1. When opening the project, make sure to check "Search for nested projects".
2. Open a file under the `WLoopCAN` directory
3. Under `Project -> Properties`, click on `C/C++ Build` 
4. Under `MCU Settings`, select the correct MCU and configure the settings (should be fairly straight forward)
5. Under `MCU GCC Compiler -> Preprocessor`, define the name of your board (the default is `MASTER_BMS`, a list of names can be found in `inc/config.h`)
6. Under `MCU GCC Compiler -> Include Paths`, correct the include paths for your MCU (default is for `STM32F405RGTx`)
7. Hit `Apply and Close`

Finally, you can build by clicking the hammer button in the top let.

### GNU Make

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

### STM32CubeIDE

Follow the following instructions:

1. Open the `Project -> Properties` menu, then open `C/C++ Build -> Settings`
2. Under `MCU GCC Compiler -> Include Paths`, add `../../WLoopCAN/inc`
3. Under `MCU GCC Compiler -> Preprocessor` add the name of your board (a list of names can be found in `inc/config.h`)
4. Under `MCU GCC Linker -> Miscellaneous` add `../../WLoopCAN/Debug/wloop_can.a` to additional object files

### GNU Make

Link `./WLoopCAN/bin/wloop_can.a` with the rest of your object files, and add `-I ./WLoopCAN/inc` to your compilation flags.

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
    if ( CANBus_init(&hcan1) != HAL_OK) { Error_Handler(); }

    if (CANBus_subscribe(BATTERY_PACK_CURRENT) != HAL_OK) { Error_Handler(); };

    CANFrame tx_frame = CANFrame_init(BATTERY_PACK_CURRENT.id);
    CANFrame_set_field(&tx_frame, BATTERY_PACK_CURRENT, FLOAT_TO_UINT(4.20));
    CANFrame_set_field(&tx_frame, CELL_TEMPERATURE, FLOAT_TO_UINT(69.420));

    while (1) {
        if (CANBus_put_frame(&tx_frame) != HAL_OK) { Error_Handler(); }
        if (!Queue_empty(&RX_QUEUE)) {
            CANFrame rx_frame = CANBus_get_frame();

            float batt_curr = UINT_TO_FLOAT(CANFrame_get_field(&rx_frame, BATTERY_PACK_CURRENT));
            float cell_temp = UINT_TO_FLOAT(CANFrame_get_field(&rx_frame, CELL_TEMPERATURE));

            printf("batt_curr = %.4f\r\n", batt_curr);
            printf("cell_temp = %.4f\r\n", cell_temp);
        }
    }
    /* USER CODE END 2 */

    return 0;
}
```

