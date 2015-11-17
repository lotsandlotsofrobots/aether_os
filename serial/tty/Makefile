ifndef ROOT
ROOT=..
endif

include $(ROOT)/globals.mk

OBJECTS = serial.o

CFLAGS+=-I$(ROOT)/include

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
