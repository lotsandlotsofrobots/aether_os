#include "io.h"
#include "serial.h"

void init_console()
{
    clear_screen();
    set_foreground_color(CONSOLE_RED);
    set_background_color(CONSOLE_GREEN);
    set_console_position(0,0);
}


void init_debug_port()
{
    #define DEBUG_COM 1
    set_serial_baud_rate(DEBUG_COM, 115200);
    set_serial_line_control_settings(DEBUG_COM, 8, false, 1);
    set_serial_fifo_settings(DEBUG_COM, SERIAL_FIFO_TRIGGER_14b_56bW, false);
    set_rts(DEBUG_COM);
}


int main()
{
    init_console();
    clear_screen();
    
    printf("hello\n\0");
    printf("This is a test\n\0");

    //init_debug_port();
    
    printf("set up the serial port\n\0");

    serial_write(DEBUG_COM,'a');
    serial_write(DEBUG_COM,'!');
    serial_write(DEBUG_COM,'P');
    serial_write(DEBUG_COM,'7');

    printf("serial_write done\n\0");
/*
    char c[64];
    uint16_t bytes_read = serial_read(DEBUG_COM, c, 64);

    printf("Bytes read:\n\0");
    if (bytes_read == 0 ) printf("zero");
    else if (bytes_read > 0 && bytes_read < 10)
    {
        printf("More than 0 but less than ten\n\0");
    }
    else if (bytes_read >= 10 && bytes_read <=64) printf("10-64\n\0");
    else if (bytes_read > 64) printf("a lot\n\0");

    printf(c);
*/
    while ( 1 ) {
	
    }
}
