

#ifndef _IIC_H_
#define _IIC_H_

#include "config.h"
#include "Port.h"

void IIC_start(void);
void IIC_stop(void);
void IIC_tack(void);
void IIC_notack(void);
void IIC_write_byte(uint8 byte);
uint8 IIC_read_byte(void);

#endif