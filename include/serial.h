#ifndef SERIAL_H
#define SERIAL_H

#include "types.h"

#define COM_DATA_BUFFER_DLAB_BIT     8
#define COM_DATA_BUFFER_DLAB         (1<<COM_DATA_BUFFER_DLAB_BIT)

#define SERIAL_LINE_ENABLE_DLAB      0x80


#define COM1                          0x03F8
#define COM2                          0x02F8

#define COM_BASE(c)                      (c == 1 ? COM1 : (c == 2 ? COM2 : 0) )
#define COM_IRQ_ENABLE(c)                COM_BASE(c) + 1
#define COM_DATA_BUFFER(c)               COM_BASE(c) + 1
#define COM_IRQ_ID(c)                    COM_BASE(c) + 2
#define COM_FIFO(c)                      COM_BASE(c) + 2
#define COM_LINE_CONTROL(c)              COM_BASE(c) + 3
#define COM_MODEM_CONTROL(c)             COM_BASE(c) + 4
#define COM_LINE_STATUS(c)               COM_BASE(c) + 5
#define COM_MODEM_STATUS(c)              COM_BASE(c) + 6
#define COM_SCRATCH(c)                   COM_BASE(c) + 7

typedef enum { 
	BAUD_RATE_9600 = 9600,
	BAUD_RATE_19200 = 19200,
	BAUD_RATE_38400 = 38400,
	BAUD_RATE_57600 = 57600,
	BAUD_RATE_115200 = 115200
} com_baud_rate_t;

typedef enum {
	SERIAL_FIFO_TRIGGER_1b_1bW   = (0x0 << 6),
	SERIAL_FIFO_TRIGGER_4b_16bW  = (0x1 << 6),
	SERIAL_FIFO_TRIGGER_8b_32bW  = (0x2 << 6),
	SERIAL_FIFO_TRIGGER_14b_56bW = (0x3 << 6),
} serial_fifo_trigger_size_t;

#define RESET_SERIAL_FIFO		0x3
#define WIDE_SERIAL_FIFO               (0x1 << 5)
#define DEFAULT_SERIAL_FIFO            (0x0 << 5)

#define SERIAL_1_STOP_BIT       (0x00 << 2)
#define SERIAL_2_STOP_BIT	(0x01 << 2)

#define SERIAL_5_DATA_BITS	0x00
#define SERIAL_6_DATA_BITS	0x01
#define SERIAL_7_DATA_BITS	0x02
#define SERIAL_8_DATA_BITS	0x03

#define SERIAL_NO_PARITY        (0x0 << 3)

void set_serial_baud_rate(uint8_t c, com_baud_rate_t baud_rate);
void set_serial_line_control_settings(uint8_t com, uint8_t data_bits, uint8_t stop_bits, uint8_t parity);
void set_serial_fifo_settings(uint8_t com, serial_fifo_trigger_size_t trigger_size_setting, uint8_t enable_wide_fifo);

void serial_write(uint8_t com, unsigned char c);
//char read_serial(uint8_t com);

uint8_t serial_read(uint8_t com, char *buffer, uint8_t buffersize);
void set_serial_rts(uint8_t com);

#endif // SERIAL_H

