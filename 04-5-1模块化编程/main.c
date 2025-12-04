#include <at89c51RC2.h>
#include "Delay.h"
#include "Nixie.h"




void main()
{
	while(1)
	{
		Nixie(1,1);		//在数码管的第1位置显示1
		Nixie(2,2);		//在数码管的第2位置显示2
		Nixie(3,3);		//在数码管的第3位置显示3
	}

}