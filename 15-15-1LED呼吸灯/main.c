#include <at89c51RC2.h>

sbit LED = P2^1;

void Delay(unsigned int t)
{
	while(t--);
}



void main()
{
	unsigned char Time,i;
	
	while(1)
	{
		for(Time=0;Time<50;Time++)
		{
			for(i=0;i<=10;i++)
			{
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(250-Time);
			}
			
		}
		
		for(Time=50;Time>0;Time--)
		{
			for(i=0;i<=10;i++)
			{
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(250-Time);
			}
			
		}
	}
}