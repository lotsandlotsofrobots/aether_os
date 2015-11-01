CC = gcc
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra  -c
LDFLAGS = -T $(ROOT)/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf
