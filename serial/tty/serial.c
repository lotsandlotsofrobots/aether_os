#include <serial.h>

void set_serial_baud_rate(unsigned short c, com_baud_rate_t baud_rate)
{
    unsigned int divisor = 115200 / (unsigned int) baud_rate;

    // get the line control value so we can 
    // set the DLAB value and remove it again later
    uint8_t line_control = inb( COM_LINE_CONTROL(c) );
    
    uint8_t divisor_high = ( (divisor && 0xFF00 ) >> 8 );
    uint8_t divisor_low  = ( divisor && 0x00FF );


    outb( COM_LINE_CONTROL(c), COM_DATA_BUFFER_DLAB_BIT );
    outb( COM_BASE(c), divisor_low );
    outb( COM_DATA_BUFFER(c), divisor_high );

    // line control & 0x7F = everything that was there - 10000000b
    outb( COM_LINE_CONTROL(c), line_control & 0x7F );
}


void set_serial_line_control_settings(uint8_t com, uint8_t data_bits, bool stop_bits, uint8_t parity)
{
    uint8_t line_control = 0x0;

    line_control |= (data_bits) & 0x03;
    line_control |= (stop_bits) & 0x04;
    line_control |= (parity) & 0x38;

    outb( COM_LINE_CONTROL(com), line_control );
}


