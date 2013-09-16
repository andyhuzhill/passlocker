/***************************************************
**�ļ���  ��Port.h
**����    �������йصĶ���
**�������ڣ�13/09/09
**�汾    ��Ver1.0
**�޸ļ�¼��
*****************************************************/

#ifndef PORT_H_
#define PORT_H_

#include "config.h"
#include "8052.h"

/*ʹ�����·��涨�������йص���Ϣ*/

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
