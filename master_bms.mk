# Master BMS variables

BOARD = MASTER_BMS
# BOARD = MOTOR_CONTROLLER
# BOARD = RING_ENCODER
# BOARD = PRESSURE_SENSOR
# BOARD = LV_POWER
# BOARD = TEMP_SENSOR

DEVICE = STM32F405RGTx
DEVICE_VARIANT = STM32F405xx
DEVICE_FAMILY = STM32F4xx

CPU = -mcpu=cortex-m0
#FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=soft
