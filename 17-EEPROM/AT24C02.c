#include <at89c51RC2.h>
#include "I2C.h"

/* AT24C02 地址说明：
   - 7-bit 地址通常是 0x50（1010 000）
   - 8-bit 地址（含 R/W 位）写为 0xA0，读为 0xA1
   这里用宏同时提供 7-bit 和左移后的 8-bit 形式，便于理解与使用。 */
#define AT24C02_ADDR7       0x50
#define AT24C02_ADDRESS     (AT24C02_ADDR7 << 1)   /* 0xA0: 设备地址（写时） */

/**
  * @brief  AT24C02 写入一个字节
  * @param  WordAddress 要写入字节的地址（0~255）
  * @param  Data 要写入的数据
  * @retval 无
  */
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data)
{
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS);    /* 设备地址 + 写(0) */
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress);        /* 要写入的内存地址 */
    I2C_ReceiveAck();
    I2C_SendByte(Data);               /* 写入数据 */
    I2C_ReceiveAck();
    I2C_Stop();

    /* 注意：AT24C02 写入需要写周期（内部写入耗时，如几 ms）。
       更健壮的实现可以在此处做写周期等待（轮询 ACK 或延时）。
       例如轮询设备地址直到 ACK（写完成），或简单 delay。*/
}

/**
  * @brief  AT24C02 读取一个字节
  * @param  WordAddress 要读出字节的地址（0~255）
  * @retval 读出的数据
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
    unsigned char Data;

    /* 先写入要读取的内存地址（随机读需要先发送地址） */
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS);    /* 设备地址 + 写(0) */
    I2C_ReceiveAck();
    I2C_SendByte(WordAddress);        /* 指定要读取的地址 */
    I2C_ReceiveAck();

    /* 重复启动并切换到读模式 */
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS | 0x01); /* 设备地址 + 读(1) */
    I2C_ReceiveAck();
    Data = I2C_ReceiveByte();         /* 读取数据 */

    I2C_SendAck(1); /* 读结束后主机发送 NACK（1 表示 NACK，0 表示 ACK，具体取决于 I2C 库实现） */
    I2C_Stop();

    return Data;
}
