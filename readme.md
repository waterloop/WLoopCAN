# WLoop CAN Libary

A minimal implementation of a CAN library for G5. Handles sending and receiving CAN frames from the bus.

## Installation

```bash
cd /path/to/stm32_project
git submodule add "https://github.com/waterloop/WLoopCAN.git"
git submodule update --init --recursive --remote
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

## .IOC CAN Configuration

Refer to the settings in `.ioc-settings`.

Make sure that RX interrupts are enabled.

## Building

### Configuration

Enable or disable features from the build by editing `feature_flags.mk`. All features are enabled by default.

### STM32CubeIDE

Open in STM32CubeIDE. From the topbar, select `Project -> Properties`, then click on `C/C++ Build`. Under `Builder Settings`, change the `Build command` to the appropriate board. For example, for the Master BMS you would change the command to:

```bash
make master_bms
```

### GNU Make

**Dependencies**

* `arm-none-eabi-gcc`
* `GNU Make`

Build using the board name.

```bash
# ex. for master_bms
make master_bms
```

## Linking With STM32 Project

### STM32CubeIDE

Follow the following instructions:

1. Open the `Project -> Properties` menu, then open `C/C++ Build -> Settings`
2. Under `MCU GCC Compiler -> Include Paths`, add `../../WLoopCAN/include`
3. Under `MCU GCC Compiler -> Preprocessor` add the name of your board (a list of names can be found in `inc/config.h`)
4. Under `MCU GCC Linker -> Miscellaneous` add `../../WLoopCAN/bin/wloop_can.a` to additional object files

### GNU Make

Follow the following instructions:

1. Add `-I ./WLoopCAN/include` to your compilation flags
2. Add `-D <board_name>` to your compilation flags (a list of names can be found in `inc/config.h`)
3. Link `./WLoopCAN/bin/wloop_can.a` with the rest of your object files

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
    if (CANBus_init(&hcan1) != HAL_OK) { Error_Handler(); }

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

