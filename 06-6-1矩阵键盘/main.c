#include <at89c51RC2.h>
#include "MatrixKey.h"
#include "LCD1602.h"
#include "Delay.h"

unsigned char MKey = 0;
unsigned char InputBuf[3];   // 最多输入3位数字
unsigned char Index = 0;     // 当前输入位置
unsigned char k;
unsigned int COMP = 0;       // 存储确认后的数字结果

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Enter Num:");   // 第一行提示

	while(1)
	{
		MKey = MatrixKey();  // 获取按键键码

		if(MKey != 0)
		{
			if(MKey >= 1 && MKey <= 10)	// 数字键
			{
				unsigned char num;
				if(MKey == 10) num = 0;     // 10号键表示“0”
				else num = MKey;            // 其他键对应数字本身

				if(Index < 3)                 // 最多3位数字
				{
					InputBuf[Index] = num;     // 存入数组
					
					// 显示输入内容
					LCD_ShowString(2,1,"        "); // 清空第二行
					for(k=0; k<=Index; k++)
					{
						LCD_ShowNum(2,k+1,InputBuf[k],1);
					}
					Index++;
				}
			}
			else if(MKey == 11) // 确认键
			{
				// 计算COMP的值，例如输入 1 2 3 => COMP=123
				COMP = 0;
				for(k=0; k<Index; k++)
				{
					COMP = COMP * 10 + InputBuf[k];
				}

				// 显示确认信息与结果
				LCD_ShowString(2,1,"Confirmed!");
				Delay(800);
				LCD_ShowString(2,1,"Value:");
				LCD_ShowNum(2,7,COMP,3);  // 显示确认的数字
				Delay(1000);

				// 清空准备下一次输入
				LCD_ShowString(2,1,"            ");
				Index = 0;
				COMP = 0;
			}
		}
	}
}
