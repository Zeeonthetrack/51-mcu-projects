#include <at89c51RC2.h>
#include "Delay.h"

void main()
{
	while(1)
	{
		if(P3_1 == 0)
		{
			Delay(20);
			while(P3_1 == 0)
			Delay(20);
			
			P2_0=~P2_0;
		}
	}
}