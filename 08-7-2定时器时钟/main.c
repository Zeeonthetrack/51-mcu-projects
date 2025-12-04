#include <at89c51RC2.h>
#include "Timer0.h"



void main()
{
	Timer0Init();
	while(1)
	{
		
	}
}


void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		P2_0=~P2_0;
	}
}