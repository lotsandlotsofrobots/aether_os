#ifndef SERIAL_H
#define SERIAL_H

#define COM_DATA_BUFFER_DLAB_BIT     0x80

#define COM1                          0x03F8
#define COM2                          0x02F8

#define COM_DATA_BUFFER(com)             (com + 1)
#define COM_FIFO(com)                    (com + 2)
#define COM_LINE_CONTROL(com)            (com + 3)
#define COM_MODEM_CONTROL(com)           (com + 4)
#define COM_LINE_STATUS(com)             (com + 5)
#define COM_MODEM_STATUS(com)            (com + 6)
#define COM_SCRATCH(com)                 (com + 7)

typedef enum { 
	BAUD_RATE_9600 = 9600,
	BAUD_RATE_19200 = 19200,
	BAUD_RATE_38400 = 38400,
	BAUD_RATE_57600 = 57600,
	BAUD_RATE_115200 = 115200
} com_baud_rate_t;


#endif // SERIAL_H

