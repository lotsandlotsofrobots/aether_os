ifndef ROOT
ROOT=..
endif

include $(ROOT)/globals.mk

OBJECTS = tty.o

all: $(OBJECTS)

install:
	cp $(OBJECTS) $(OBJS_DIR)/

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm *.o
