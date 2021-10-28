BUILD_DIR = bin

all:
	@echo 'no rule to build "all", must specify board...'

master_bms:
	make -f master_bms.makefile

ring_encoder:
	make -f ring_encoder.makefile

clean:
	rm -rf $(BUILD_DIR)

