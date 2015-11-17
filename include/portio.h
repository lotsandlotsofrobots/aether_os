#ifndef PORTIO_H
#define PORTIO_H

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

//void s_outb(unsigned short port, char data);
//char s_inb(unsigned short port);


#endif // PORTIO_H

