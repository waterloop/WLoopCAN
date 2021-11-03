BOARD = RING_ENCODER
# BOARD = MASTER_BMS
# BOARD = MOTOR_CONTROLLER
# BOARD = PRESSURE_SENSOR
# BOARD = LV_POWER
# BOARD = TEMP_SENSOR

DEVICE = STM32F042K4Tx
DEVICE_VARIANT = STM32F042x6
DEVICE_FAMILY = STM32F0xx

CPU = -mcpu=cortex-m0
#FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=soft
