#include <at89c51RC2.h>
#include "Key.h"
#include "Nixie.h"
#include "Delay.h"

sbit Buzzer = P2^5;

unsigned char KeyNum;
unsigned int i;

void main()
{
	Nixie(1,0);
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			for(i=0;i<250;i++)
			{
				Buzzer=!Buzzer;
				Delay(1);
			}
			Nixie(1,KeyNum);
		}
	}
}
