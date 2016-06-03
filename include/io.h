#ifndef IO_H
#define IO_H

#define CONSOLE_BLACK        0x0
#define CONSOLE_BLUE         0x1
#define CONSOLE_GREEN        0x2
#define CONSOLE_CYAN         0x3
#define CONSOLE_RED          0x4
#define CONSOLE_MAGENTA      0x5
#define CONSOLE_BROWN        0x6
#define CONSOLE_LT_GREY      0x7
#define CONSOLE_DK_GREY      0x8
#define CONSOLE_LT_BLUE      0x9
#define CONSOLE_LT_GREEN     0xA
#define CONSOLE_LT_CYAN      0xB
#define CONSOLE_LT_RED       0xC
#define CONSOLE_LT_MAGENTA   0xD
#define CONSOLE_LT_BROWN     0xE
#define CONSOLE_WHITE        0xF


//void __lowlevel_write_char(unsigned int address, unsigned int value);
//void printc(unsigned int r, unsigned int c, unsigned char ch, unsigned char fg, unsigned char bg);

void printc(unsigned char ch);
void writechar(void);
void clear_screen(void);

//void printf(unsigned int r, unsigned int c, char *msg, unsigned char fg, unsigned char bg);
void kprintf(char *msg);
unsigned int set_console_position(unsigned int r, unsigned int c);
unsigned int set_clear_color(unsigned char color);
unsigned int set_foreground_color(unsigned char color);
unsigned int set_background_color(unsigned char color);

#endif
