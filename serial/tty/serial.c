#include "serial.h"
#include "portio.h"
#include "io.h"

#define SERIAL_DISABLE_IRQ(com) 	outb( COM_IRQ_ENABLE(com), 0x0 );

#define DLAB_ON(com)			outb( COM_LINE_CONTROL(com), 0x80 );
#define DLAB_OFF(com)			outb( COM_LINE_CONTROL(com), 0x0 );

#define READ_LINE_CONTROL(com)		inb( COM_LINE_CONTROL(com) );

#define SET_BAUD_LOW(com, baud_l)	outb( COM_BASE(com), baud_l );
#define SET_BAUD_HIGH(com, baud_h)	outb( COM_DATA_BUFFER(com), baud_h );


void set_serial_baud_rate(uint8_t com, com_baud_rate_t baud_rate)
{
    unsigned int divisor = 115200 / (unsigned int) baud_rate;
    divisor = 1;

    SERIAL_DISABLE_IRQ(com)

    uint8_t divisor_high = ( (divisor && 0xFF00 ) >> 8 );
    uint8_t divisor_low  = ( divisor && 0x00FF );

    divisor_high = 0;
    divisor_low = 3;

    DLAB_ON(com);

    SET_BAUD_LOW( com, divisor_low );
    SET_BAUD_HIGH( com, divisor_high );

    DLAB_OFF( com );
}


void set_serial_line_control_settings(uint8_t com, uint8_t data_bits, uint8_t stop_bits, uint8_t parity)
{
    uint8_t line_control = 0x0;

    line_control |= data_bits;
    line_control |= stop_bits;
    line_control |= parity;

    outb( COM_LINE_CONTROL(com), line_control );
}


void set_serial_fifo_settings(uint8_t com, serial_fifo_trigger_size_t trigger_size_setting, uint8_t enable_wide_fifo)
{
    uint8_t settings = 0x0;

    settings |= (uint8_t) trigger_size_setting;
    settings |= enable_wide_fifo;
    settings |= RESET_SERIAL_FIFO;

    outb( COM_FIFO(com), settings );
}


void set_serial_rts(uint8_t com)
{
    outb( COM_MODEM_CONTROL(com), 0x03 );   
}


uint8_t serial_read(uint8_t com, char *buffer, uint8_t buffersize)
{
    uint8_t idx = 0;

    while ( ( inb( COM_LINE_CONTROL(com) ) & 1 ) == 1 && idx < buffersize )
    {
        buffer[idx] = inb( COM_BASE(com) );
        idx++;
    }

    return idx;

/*
    for (t = 0; t < timeout; t++)
    {
        if ( ( u_inb( COM_LINE_CONTROL(com) ) & 1 ) == 0 )
        {
            continue;
        }
        else
        {
            c = s_inb( COM_BASE(com) );
            return true;
        }
    }
*/
}


void serial_write(uint8_t com, unsigned char c)
{
    char ch = '.';

    while ( ( inb( COM_LINE_STATUS(com) ) & 0x20 ) == 0 ) {
        //ch += 1;
        printc(ch);
    }

    outb( COM_BASE(com), c );
}

