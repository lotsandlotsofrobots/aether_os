#include "io.h"
#include "types.h"

#include "portio.h"

#define FB_START 0xB8000

void __lowlevel_write_char(unsigned int address, unsigned char ch, unsigned short color_settings);

typedef struct __attribute__((packed)) console_settings {
    unsigned char row;
    unsigned char col;
    unsigned char fg;
    unsigned char bg;
    unsigned char clear_color;
} console_settings;

console_settings settings;


unsigned int set_clear_color(unsigned char color)
{
    if ( color > 0xF )
    {
        //printf("Error:  invalid color passed to setClearColor");
        return 1;
    }

    settings.clear_color = color;
    return 0;
}


unsigned int set_foreground_color(unsigned char color)
{
    if ( color > 0xF )
    {
        //printf("Error:  invalid color passed to setClearColor");
        return 1;
    }

    settings.fg = color;
    return 0;
}


unsigned int set_background_color(unsigned char color)
{
    if ( color > 0xF )
    {
	//printf("Error:  invalid color passed to setClearColor");
	return 1;
    }

    settings.bg = color;
    return 0;
}


void increment_console_position(int places)
{
    int rows = 0;
    int cols = places;

    unsigned int prevCols = settings.col;

    //cols = prevCols + places;
    if ( prevCols + places >= 80 )
    {
        rows += (prevCols + places) % 80;
        cols -= 80;
    }

    settings.row += rows;
    settings.col += cols;

}


void line_wrap()
{
    settings.row += 1;
    settings.col = 0;
}



unsigned int set_console_position(unsigned int r, unsigned int c)
{
    settings.row = r;
    settings.col = c;

    return 0;
}


void printc(unsigned char ch)
{
    int address = FB_START + ((( settings.row * 80) + settings.col ) * 2) ;

    char char_settings = ((settings.bg & 0x0F) << 4) | (settings.fg & 0x0F) ;

    char *framebuffer = (char *) address;
    framebuffer[0] = ch & 0xFF;
    framebuffer[1] = char_settings;

    increment_console_position(1);
}


void printf(char *msg)
{
    int i = 0;
    for (i = 0; msg[i] != '\0'; i++)
    {
        if ( msg[i] == '\n' || msg[i] == '\r' )
        {
            line_wrap();
            continue;
        }

        printc(msg[i]);
    }
}


void clear_screen()
{
    int r = 0;
    int c = 0;

    char *framebuffer = (char *) 0x000B8000;

    for (r = 0 ; r < 24; r++)
    {
        for(c = 0; c < 80; c++)
        {
            framebuffer[r*80 + c] = 0x0;
            framebuffer[r*80 + c + 1] = 0x0;
        }
    }

}

