#include <at89c51RC2.h>

/* 如果你想换引脚，只改下面两行 */
#define I2C_SCL    P2_1    /* SCL 线 -> P2.1 */
#define I2C_SDA    P2_0    /* SDA 线 -> P2.0 */

/* 简单延时（防止总线切换太快）。根据你的晶振可适当调整循环次数。 */
static void I2C_Delay(void)
{
    volatile unsigned char i;
    for(i = 0; i < 10; i++); /* 空循环延时（防止被优化） */
}

/**
  * @brief  I2C 开始
  */
void I2C_Start(void)
{
    I2C_SDA = 1;    /* 释放 SDA（高电平）*/
    I2C_SCL = 1;    /* 释放 SCL（高电平）*/
    I2C_Delay();
    I2C_SDA = 0;    /* SDA 由高到低，SCL 保持高 => START */
    I2C_Delay();
    I2C_SCL = 0;
    I2C_Delay();
}

/**
  * @brief  I2C 停止
  */
void I2C_Stop(void)
{
    I2C_SDA = 0;
    I2C_Delay();
    I2C_SCL = 1;
    I2C_Delay();
    I2C_SDA = 1;    /* SDA 由低到高，SCL 为高 => STOP */
    I2C_Delay();
}

/**
  * @brief  I2C 发送一个字节
  * @param  Byte 要发送的字节
  */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        /* 从高位到低位发送 */
        I2C_SDA = (Byte & (0x80 >> i)) ? 1 : 0;
        I2C_Delay();
        I2C_SCL = 1;
        I2C_Delay();
        I2C_SCL = 0;
        I2C_Delay();
    }
}

/**
  * @brief  I2C 接收一个字节
  * @retval 接收到的一个字节数据
  */
unsigned char I2C_ReceiveByte(void)
{
    unsigned char i;
    unsigned char Byte = 0x00;

    I2C_SDA = 1; /* 释放 SDA，由从机驱动数据线 */
    for(i = 0; i < 8; i++)
    {
        I2C_Delay();
        I2C_SCL = 1;
        I2C_Delay();
        if(I2C_SDA)      /* 读高位到低位 */
        {
            Byte |= (0x80 >> i);
        }
        I2C_SCL = 0;
    }
    return Byte;
}

/**
  * @brief  I2C 发送应答（主机发送给从机）
  * @param  AckBit 应答位，0 为 ACK（继续），1 为 NACK（结束）
  */
void I2C_SendAck(unsigned char AckBit)
{
    I2C_SDA = AckBit ? 1 : 0;
    I2C_Delay();
    I2C_SCL = 1;
    I2C_Delay();
    I2C_SCL = 0;
    I2C_Delay();
    I2C_SDA = 1; /* 通常发送完应答后释放 SDA（以便下次从机驱动）*/
}

/**
  * @brief  I2C 接收应答位（主机发送地址/数据后从机返回的 ACK）
  * @retval 接收到的应答位，0 为 ACK，1 为 NACK
  */
unsigned char I2C_ReceiveAck(void)
{
    unsigned char AckBit;
    I2C_SDA = 1;    /* 释放 SDA，让从机拉低表示 ACK */
    I2C_Delay();
    I2C_SCL = 1;
    I2C_Delay();
    AckBit = I2C_SDA ? 1 : 0;
    I2C_SCL = 0;
    I2C_Delay();
    return AckBit;
}
