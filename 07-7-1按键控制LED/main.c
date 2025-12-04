#include <at89c51RC2.h>
#include "Timer0.h"
#include "Key.h"

unsigned char KeyNum;

void main()
{
//	Timer0Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			if(KeyNum==1)P2_1=~P2_1;
			if(KeyNum==2)P2_2=~P2_2;
			if(KeyNum==3)P2_3=~P2_3;
			if(KeyNum==4)P2_4=~P2_4;
		}
	}
}


//void Timer0_Routine() interrupt 1
//{
//	static unsigned int T0Count;
//	TL0 = 0x18;		//设置定时初值
//	TH0 = 0xFC;		//设置定时初值
//	T0Count++;
//	if(T0Count>=1000)
//	{
//		T0Count=0;
//		P2_0=~P2_0;
//	}
//}