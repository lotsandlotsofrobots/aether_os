#include "io.h"

void initConsole()
{
    setForegroundColor(0x4);
    setBackgroundColor(0x15);
    setConsolePosition(0,0);
}

int main()
{
    initConsole();
    clearscreen();
    //printc(0, 0, 'a', FB_GREEN, FB_GREEN);
    printf("hello\0");
    printf("This is a test\0");

    //printc(0, 1, 'b', FB_GREEN, FB_BLACK);
    //printc(0, 2, 'c', FB_GREEN, FB_BLACK);
    //printc(0, 0, 'z', FB_GREEN, FB_BLACK);
    //clearscreen();
    //writechar();

    while ( 1 ) {
	
    }
}
