#include <at89c51RC2.h>
#include "Delay.h"
#include "Nixie.h"
#include "Key.h"
#include "Timer0.h"

unsigned char Counter,Compare;
unsigned char KeyNum,Speed;


sbit Motor = P1^0;



void main()
{
	Timer0Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum==1)
		{
			Speed++;
			Speed%=4;
			if(Speed==0){Compare=0;}
			if(Speed==1){Compare=30;}
			if(Speed==2){Compare=60;}
			if(Speed==3){Compare=90;}
		}
		Nixie(1,Speed);
	}
}



void Timer0_Routine() interrupt 1
{
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	Counter++;
	Counter%=100;
	if(Counter<Compare)
	{
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
}
