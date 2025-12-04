#include <at89c51RC2.h>
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"
#include "Delay.h"

unsigned char KeyNum;
unsigned int Num = 0;   /* 初始化，避免随机值 */

/* 如果你不想在启动时从 EEPROM 恢复上次值，
   可把下面 startup 读取的部分删掉。 */

void main()
{
    /* 初始化显示与外设 */
    LCD_Init();

    /* 启动时尝试从 AT24C02 恢复之前保存的 Num（低字节在地址0，高字节在地址1） */
    Num = AT24C02_ReadByte(0);           /* 低 8 位 */
    Num |= (unsigned int)AT24C02_ReadByte(1) << 8;  /* 高 8 位 */

    /* 显示初始值 */
    LCD_ShowNum(1, 1, Num, 5);

    while(1)
    {
        KeyNum = Key();    /* 读取按键，Key() 返回 0/1/2/3/4 等 */

        if(KeyNum == 1)    /* K1 按键，Num 自增 */
        {
            Num++;
            LCD_ShowNum(1, 1, Num, 5);
        }
        else if(KeyNum == 2) /* K2 按键，Num 自减 */
        {
            Num--;
            LCD_ShowNum(1, 1, Num, 5);
        }
        else if(KeyNum == 3) /* K3 按键，向 AT24C02 写入数据（低字节地址0，高字节地址1） */
        {
            AT24C02_WriteByte(0, (unsigned char)(Num & 0xFF));    /* 低字节 */
            Delay(5); /* 给 EEPROM 写入时间，或采用 ACK 轮询更可靠 */
            AT24C02_WriteByte(1, (unsigned char)((Num >> 8) & 0xFF)); /* 高字节 */
            Delay(5);

            LCD_ShowString(2, 1, "Write OK");
            Delay(1000);
            LCD_ShowString(2, 1, "        ");
        }
        else if(KeyNum == 4) /* K4 按键，从 AT24C02 读取数据并显示 */
        {
            Num = AT24C02_ReadByte(0);
            Num |= (unsigned int)AT24C02_ReadByte(1) << 8;
            LCD_ShowNum(1, 1, Num, 5);

            LCD_ShowString(2, 1, "Read OK ");
            Delay(1000);
            LCD_ShowString(2, 1, "        ");
        }

        /* 其它 KeyNum（如 0）表示无键按下，循环继续 */
    }
}
