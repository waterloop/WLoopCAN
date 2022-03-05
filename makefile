BUILD_DIR = bin

all:
	@echo 'Error: no rule to build "all", must specify board (ex. make master_bms)'
	@echo ""

master_bms:
	make -f main.mk \
		BUILD_DIR=$(BUILD_DIR) \
		BOARD_VARS="master_bms.mk"

motor_controller:
	make -f main.mk \
		BUILD_DIR=$(BUILD_DIR) \
		BOARD_VARS="motor_controller.mk"

ring_encoder:
	make -f main.mk \
		BUILD_DIR=$(BUILD_DIR) \
		BOARD_VARS="ring_encoder.mk"

pressure_sensor:
	make -f main.mk \
		BUILD_DIR=$(BUILD_DIR) \
		BOARD_VARS="pressure_sensor.mk"

lv_power:
	make -f main.mk \
		BUILD_DIR=$(BUILD_DIR) \
		BOARD_VARS="lv_power.mk"

pod_indicator_light:
	make -f main.mk \
		BUILD_DIR=$(BUILD_DIR) \
		BOARD_VARS="pod_indicator_light.mk"


clean:
	rm -rf $(BUILD_DIR)
