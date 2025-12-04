#include <at89c51RC2.h>
#include "Delay.h"
#include "UART.h"
#include "Nixie.h"

unsigned int Sec;
unsigned char Counter;

void main()
{
	UART_Init();
	
	while(1)
	{
		UART_SendByte(30);		
		Delay(250);
	}
}



