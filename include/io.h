#ifndef IO_H
#define IO_H

#define FB_BLACK 0x0
#define FB_GREEN 0x2

//void __lowlevel_write_char(unsigned int address, unsigned int value);
//void printc(unsigned int r, unsigned int c, unsigned char ch, unsigned char fg, unsigned char bg);
void printc(unsigned char ch);
void writechar(void);
void clearscreen(void);
//void printf(unsigned int r, unsigned int c, char *msg, unsigned char fg, unsigned char bg);
void printf(char *msg);
unsigned int set_console_position(unsigned int r, unsigned int c);
unsigned int set_clear_color(unsigned char color);
unsigned int set_foreground_color(unsigned char color);
unsigned int set_background_color(unsigned char color);

#endif
