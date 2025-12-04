#include <at89c51RC2.h>
#include "Delay.h"
#include "UART.h"


unsigned char Sec;

void main()
{
	UART_Init();
	Sec=0;
	while(1)
	{
		Sec++;
		UART_SendByte(Sec);
		Delay(500);
	}
}




