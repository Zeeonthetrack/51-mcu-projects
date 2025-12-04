#include <at89c51RC2.h>

void Timer0_Init()
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;		
}



void main()
{
	Timer0_Init();
	while(1)
	{
		
	}
}

unsigned int T0Count;
void Timer0_Routine() interrupt 1
{
	TH0=64535/256;
	TL0=64535%256;
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		P2_4=~P2_4;
	}
}


