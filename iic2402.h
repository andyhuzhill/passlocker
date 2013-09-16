

#ifndef __IIC2402_H_
#define  __IIC2402_H_

#include "config.h"
#include "Port.h"
#include "iic.h"

void iic2402_write(uint8 address, uint8 byte);
uint8 iic2402_read(uint8 address);

#endif