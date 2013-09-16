/***************************************************
**文件名  ：Port.h
**功能    ：引脚有关的定义
**建立日期：13/09/09
**版本    ：Ver1.0
**修改记录：
*****************************************************/

#ifndef PORT_H_
#define PORT_H_

#include "config.h"
#include "8052.h"

/*使用如下方面定义引脚有关的信息*/

#define  SCL    P3_2
#define  SCL_LOW    (SCL = 0)
#define  SCL_HIGH   (SCL = 1)

#define  SDA    P3_3
#define  SDA_LOW    (SDA = 0)
#define  SDA_HIGH   (SDA = 1)

#define  KEY_PORT  P2

#define  LED_COM1  P3_4
#define  LED_COM2  P3_5
#define  LED_COM3  P3_6
#define  LED_COM4  P3_7
#define  LED_PORT  P0

#endif
