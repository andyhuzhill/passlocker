/***************************************************
**文件名  ：config.h
**功能    ：CPU有关的配置
**建立日期：13/09/09
**版本    ：Ver1.0
**修改记录：
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

/*系统时钟*/
#define Fosc   11059200 		/*HZ					*/
#define PER_INS_CYC    12  	/*12时钟周期为一个机器周期*/

#define _nop_() __asm  \
                  nop   \
		 __endasm
		 
#endif


