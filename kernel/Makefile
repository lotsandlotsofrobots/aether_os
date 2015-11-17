ifndef ROOT
$(info ROOT is not defined.)
ROOT=..
endif

include $(ROOT)/globals.mk

OBJECTS = kmain.o portio.o

CFLAGS+=-I$(ROOT)/include

#CC = gcc
#CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
#LDFLAGS = -T ../link.ld -melf_i386
#AS = nasm
#ASFLAGS = -f elf

all: kernel

install:
	cp $(OBJECTS) $(OBJS_DIR)/

kernel: $(OBJECTS)
	$(info ROOT is $(ROOT))

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm *.o kernel
