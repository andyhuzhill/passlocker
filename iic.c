
#include "iic.h"


void
IIC_start(void)
{
    SDA_HIGH;
    SCL_HIGH;
    _nop_();
    _nop_();

    SDA_LOW;
    _nop_();
    _nop_();

    SCL_LOW;
}

void
IIC_stop(void)
{
    SDA_LOW;
    SCL_HIGH;
    _nop_();
    _nop_();

    SDA_HIGH;
    _nop_();
    _nop_();

    SCL_LOW;
}

void
IIC_tack(void)
{
    SDA_LOW;
    SCL_HIGH;
    _nop_();
    _nop_();

    SCL_LOW;
}
void IIC_notack(void)
{
    SDA_HIGH;
    SCL_HIGH;
    _nop_();
    _nop_();

    SCL_LOW;
}
void
IIC_write_byte(uint8 byte)
{
    uint8 cnt = 8;
    while (cnt --)
    {
        SDA = (__bit)(byte & 0x80);
        SCL_HIGH;
        _nop_();
        _nop_();
 
        SCL_LOW;
        byte <<= 1;
    }
    SCL_LOW;
}
uint8
IIC_read_byte(void)
{
    uint8 cnt = 8;
    uint8 tmp = 0;
    while (cnt--)
    {
        SDA_HIGH;
        SCL_HIGH;
        _nop_();
        _nop_();

        tmp <<= 1;
        tmp |= (uint8)SDA;
        SCL_LOW;
    }
    return tmp;
}
