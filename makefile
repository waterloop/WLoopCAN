########################################################
# USER DEFINED VARIABLES
DEBUG = true

# BOARD = MASTER_BMS
# BOARD = MOTOR_CONTROLLER
BOARD = RING_ENCODER
# BOARD = PRESSURE_SENSOR
# BOARD = LV_POWER
# BOARD = TEMP_SENSOR

DEVICE = STM32F042K4Tx
DEVICE_VARIANT = STM32F042x6
DEVICE_FAMILY = STM32F0xx

CPU = -mcpu=cortex-m0
#FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=soft
########################################################

TARGET = wloop_can.a
BUILD_DIR = bin

ifeq ($(DEBUG), true)
	OPT = -Og
else
	OPT = -O2
endif

CC = arm-none-eabi-gcc
CP = arm-none-eabi-gcc-objcopy
SZ = arm-none-eabi-size
AR = arm-none-eabi-ar

C_SOURCES = $(wildcard ./src/*.c)
ifeq ($(DEBUG), true)
	C_SOURCES += $(wildcard ./src/tests/*c)
endif

C_INCLUDES = \
-I ./inc \
-I ../$(DEVICE)/Core/Inc \
-I ../$(DEVICE)/Drivers/$(DEVICE_FAMILY)_HAL_Driver/Inc \
-I ../$(DEVICE)/Drivers/$(DEVICE_FAMILY)_HAL_Driver/Inc/Legacy \
-I ../$(DEVICE)/Drivers/CMSIS/Device/ST/$(DEVICE_FAMILY)/Include \
-I ../$(DEVICE)/Drivers/CMSIS/Include

C_DEFS = \
-D USE_HAL_DRIVER \
-D $(DEVICE_VARIANT) \
-D $(BOARD)

ifeq ($(DEBUG), true)
	-D += DEBUG
endif

MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

C_FLAGS = $(C_INCLUDES) $(C_DEFS) $(MCU) $(OPT) -ffunction-sections -fdata-sections -Wall -MMD -MP -MF"$(@:%.o=%.d)"

ifeq ($(DEBUG), true)
	C_FLAGS += -ggdb
endif

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))

.PHONY: all run clean

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(AR) rvs $(BUILD_DIR)/$(TARGET) $(OBJECTS)
	@echo ""
	$(SZ) $@
	@echo ""

$(BUILD_DIR)/%.o: ./src/%.c | $(BUILD_DIR)
	$(CC) -c $(C_FLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	@echo ""

$(BUILD_DIR)/%.o: ./src/tests/%.c | $(BUILD_DIR)
	$(CC) -c $(C_FLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	@echo ""

$(BUILD_DIR):
	mkdir $@
	@echo ""

clean:
	rm -rf $(BUILD_DIR)

