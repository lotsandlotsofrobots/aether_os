#include "serial.h"
#include "portio.h"
#include "io.h"

void set_serial_baud_rate(uint8_t com, com_baud_rate_t baud_rate)
{
    unsigned int divisor = 115200 / (unsigned int) baud_rate;

    // get the line control value so we can 
    // set the DLAB value and remove it again later
    uint8_t old_line_control = inb( COM_LINE_CONTROL(com) );
    kprintf("Old line control: \n\0" );
 
    uint8_t divisor_high = ( (divisor && 0xFF00 ) >> 8 );
    uint8_t divisor_low  = ( divisor && 0x00FF );

    outb( COM_LINE_CONTROL(com), old_line_control | COM_DATA_BUFFER_DLAB_BIT );

    outb( COM_BASE(com), divisor_low );
    outb( COM_DATA_BUFFER(com), divisor_high );

    // line control & 0x7F = everything that was there - 0111_1111b
    outb( COM_LINE_CONTROL(com), old_line_control & 0x7F );
}


void set_serial_line_control_settings(uint8_t com, uint8_t data_bits, bool parity, uint8_t stop_bits)
//void set_serial_line_control_settings(uint8_t com, uint8_t data_bits, uint8_t stop_bits, bool parity)
{
    uint8_t line_control = 0x0;

    line_control |= (data_bits) & 0x03;     // 0000_0011 b
    line_control |= (stop_bits<<2) & 0x04;  // 0000_0100 b
    line_control |= (parity<<3) & 0x38;     // 0011_1000 b

    outb( COM_LINE_CONTROL(com), line_control );
}


void set_serial_fifo_settings(uint8_t com, serial_fifo_trigger_size_t trigger_size_setting, bool enable_wide_fifo)
{
    uint8_t settings = 0x0;

    settings |= (uint8_t)trigger_size_setting << 6;
    settings |= ( enable_wide_fifo == true ? 0x10 : 0x0 );

    outb( COM_FIFO(com), settings );
}


void set_rts(uint8_t com)
{
    outb( COM_MODEM_CONTROL(com), 0x13 );
    
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


void serial_write(uint8_t com, char c)
{
/*
   uint8_t PORT = COM1_BASE;
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x01);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
*/
    char ch = 'a';

    while ( ( inb( COM_LINE_STATUS(com) ) & 0x20 ) == 0 ) {
        ch += 1;
        printc(ch);
    }

    outb( COM_BASE(com), 0x47 );
}

