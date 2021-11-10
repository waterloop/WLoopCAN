include $(BOARD_VARS)
include feature_flags.mk

TARGET = wloop_can.a

CC = arm-none-eabi-gcc
CP = arm-none-eabi-gcc-objcopy
SZ = arm-none-eabi-size
AR = arm-none-eabi-ar

OPT = -Og

ifeq ($(CAN), 1)
	C_SOURCES = $(wildcard ./can/src/*.c)
endif

ifeq ($(TESTS), 1)
	C_SOURCES += $(wildcard ./tests/src/*c)
endif

C_INCLUDES = \
-I ./can/inc \
-I ./tests/inc \
-I ../$(DEVICE)/Core/Inc \
-I ../$(DEVICE)/Drivers/$(DEVICE_FAMILY)_HAL_Driver/Inc \
-I ../$(DEVICE)/Drivers/$(DEVICE_FAMILY)_HAL_Driver/Inc/Legacy \
-I ../$(DEVICE)/Drivers/CMSIS/Device/ST/$(DEVICE_FAMILY)/Include \
-I ../$(DEVICE)/Drivers/CMSIS/Include

C_DEFS = \
-D USE_HAL_DRIVER \
-D $(DEVICE_VARIANT) \
-D $(BOARD)

ifeq ($(DEBUG), 1)
	-D += DEBUG
endif

MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

C_FLAGS = $(C_INCLUDES) $(C_DEFS) $(MCU) $(OPT) -ffunction-sections -fdata-sections -Wall -MMD -MP -MF"$(@:%.o=%.d)"

ifeq ($(DEBUG), 1)
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

$(BUILD_DIR)/%.o: ./*/src/%.c | $(BUILD_DIR)
	$(CC) -c $(C_FLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	@echo ""

$(BUILD_DIR):
	mkdir $@
	@echo ""

clean:
	rm -rf $(BUILD_DIR)

