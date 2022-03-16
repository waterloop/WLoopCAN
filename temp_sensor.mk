BOARD = TEMP_SENSOR
# BOARD = LV_POWER
# BOARD = PRESSURE_SENSOR
# BOARD = MOTOR_CONTROLLER
# BOARD = RING_ENCODER
# BOARD = MASTER_BMS

DEVICE = STM32F303K6Tx
DEVICE_VARIANT = STM32F303x8
DEVICE_FAMILY = STM32F3xx

CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
