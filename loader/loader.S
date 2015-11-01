global loader
extern writechar
extern main
extern clearscreen

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes

section .bss
align 4                                     ; align at 4 bytes
kernel_stack:                               ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov eax, 0xDEADBEEF
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call main
    ;call clearscreen
    ;call writechar
.loop:
    jmp .loop
