ROOT=$(shell pwd)

include globals.mk
include configs.mk

MODULES=loader kernel display serial
OBJECTS=$(MODULES)

OBJS_DIR=$(BUILD_DIR)/objs
INSTALL_DIR=$(BUILD_DIR)/deploy
ISO_DIR=$(BUILD_DIR)/iso

all: kernel.elf

kernel.elf: modules 
	ld $(LDFLAGS) $(OBJS_DIR)/*.o -o $(INSTALL_DIR)/kernel.elf

modules:
	for mm in $(MODULES) ; do \
	        make -C $$mm ROOT=$(ROOT) OBJS_DIR=$(OBJS_DIR) INSTALL_DIR=$(INSTALL_DIR) ; \
		make -C $$mm ROOT=$(ROOT) OBJS_DIR=$(OBJS_DIR) INSTALL_DIR=$(INSTALL_DIR) install ; \
	done

os.iso: kernel.elf
	cp boot/stage2_eltorito $(ROOTFS_DIR)/boot/
	cp $(INSTALL_DIR)/kernel.elf $(ROOTFS_DIR)/boot/kernel.elf
	cd $(BUILD_DIR) ; genisoimage -R       \
		-b boot/grub/stage2_eltorito    \
		-no-emul-boot                   \
		-boot-load-size 4               \
		-A os                           \
		-input-charset utf8             \
		-quiet                          \
		-boot-info-table                \
		-o $(ISO_DIR)/os.iso            \
		$(ROOTFS_DIR)

run: os.iso
	cd $(ISO_DIR); bochs -f $(BOCHS_DIR)/settings.txt -q

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso
	rm -f $(OBJS_DIR)/*
	rm -f $(INSTALL_DIR)/kernel.elf

cleanall:
	for mm in $(MODULES) ; do \
		make -C $$mm ROOT=$(ROOT) OBJS_DIR=$(OBJS_DIR) INSTALL_DIR=$(INSTALL_DIR) clean ; \
	done

