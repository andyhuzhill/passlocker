/***************************************************
**�ļ���  ��config.h
**����    ��CPU�йص�����
**�������ڣ�13/09/09
**�汾    ��Ver1.0
**�޸ļ�¼��
*****************************************************/
/********************************************/
#ifndef CONFIG_H_
#define CONFIG_H_

#include <8052.h>

/*type define*/
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned int uint16;
typedef signed int   sint16;
typedef unsigned long uint32;
typedef signed long  sint32;
typedef float        fp32;

/*ϵͳʱ��*/
#define Fosc   11059200 		/*HZ					*/
#define PER_INS_CYC    12  	/*12ʱ������Ϊһ����������*/

#define _nop_() __asm  \
                  nop   \
		 __endasm
		 
#endif


