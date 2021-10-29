BUILD_DIR = bin
MAKEFILES_DIR = makefiles

all:
	@echo 'no rule to build "all", must specify board...'

master_bms:
	make -f $(MAKEFILES_DIR)/master_bms.makefile

ring_encoder:
	make -f $(MAKEFILES_DIR)/ring_encoder.makefile

clean:
	rm -rf $(BUILD_DIR)

