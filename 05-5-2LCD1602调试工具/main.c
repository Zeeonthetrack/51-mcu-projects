#include <at89c51RC2.h>
#include "LCD1602.h"

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,"A");
	LCD_ShowString(1,3,"Tyler's Song");
	LCD_ShowBinNum(2,1,0xF7B,12);
	LCD_ShowNum(2,14,29,2);
	while(1)
	{
		
	}
}