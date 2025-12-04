#include <at89c51RC2.h>
#include "Delay.h"

//获取独立按键键码
//按下按键的键码，范围0~4，无按键按下时返回值为0

unsigned char Key()
{
	unsigned char KeyNumber=0;
	
	if(P3_1==0){Delay(50);while(P3_1==0);Delay(50);KeyNumber=1;}
	if(P3_0==0){Delay(50);while(P3_0==0);Delay(50);KeyNumber=2;}	
	if(P3_2==0){Delay(50);while(P3_2==0);Delay(50);KeyNumber=3;}	

	
	return KeyNumber;
}

