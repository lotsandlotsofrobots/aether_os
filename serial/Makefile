ifndef ROOT
$(info ROOT is not defined.)
ROOT=..
endif

include $(ROOT)/globals.mk

MODULES=tty

all: modules

modules:
	for mm in $(MODULES) ; do \
                make -C $$mm ROOT=$(ROOT) OBJS_DIR=$(OBJS_DIR) INSTALL_DIR=$(INSTALL_DIR) ; \
                make -C $$mm ROOT=$(ROOT) OBJS_DIR=$(OBJS_DIR) INSTALL_DIR=$(INSTALL_DIR) install ; \
        done

install:
	

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	for mm in $(MODULES) ; do \
                make -C $$mm ROOT=$(ROOT) OBJS_DIR=$(OBJS_DIR) INSTALL_DIR=$(INSTALL_DIR) clean
	done

cleanall: clean
	rm *.o
