
#include "iic2402.h"

static void delay(void)
{
    int x, y;
    for(x = 0; x<16;x ++){
        for(y=0; y<120; y++){
            _nop_();
        }
    }
}

void 
iic2402_write(uint8 address, uint8 byte)
{
   IIC_start();
   IIC_write_byte(0xa0);
   IIC_tack();
   IIC_write_byte(address);
   IIC_tack();
   IIC_write_byte(byte);
   IIC_tack();
   IIC_stop();
   delay();
}

uint8 
iic2402_read(uint8 address)
{
    uint8 tmp;
    IIC_start();
    IIC_write_byte(0xa0);
    IIC_tack();
    IIC_write_byte(address);
    IIC_tack();
    
    IIC_start();
    IIC_write_byte(0xa1);
    IIC_tack();
    tmp = IIC_read_byte();
    SCL_LOW;
    IIC_notack();
    IIC_stop();
    return tmp;
}