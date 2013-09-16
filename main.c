
#include"config.h"
#include"Port.h"

#include "iic2402.h"
#include "key.h"

typedef enum{
    ready = 0,
    inputPasswd,
    changePasswd,
} status_type;


//ȫ�ֱ������壬ע��������жϺ������жϺ���������ʹ�õı�����Ҫ���н�ֹ�жϱ���
//ͬʱ��Ҫ����������Ϊvolatile . exp: volatile u8 timer_count = 0;
//���ֻ���ڸ��ļ���ʹ�õı�����������ǰ���static
static status_type stat = ready;

static uint8
seg_code[] = {
    0xc0,   /* 0 */
    0xf9,   /* 1 */
    0xa4,   /* 2 */
    0xb0,   /* 3 */
    0x99,   /* 4 */
    0x92,   /* 5 */
    0x82,   /* 6 */
    0xf8,   /* 7 */
    0x80,   /* 8 */
    0x90,   /* 9 */
    0x88,   /* A */
    0x83,   /* B */
    0xc6,   /* C */
    0xa1,   /* D */
    0x86,   /* E */
    0x8e,   /* F */
    0xbf,   /* - (16)*/
    0x89,   /* H (17)*/
    0xff    /* �հ� (18)*/
};  //��������ܶ���

static void
delay(void)
{
    uint8 i, j;
    for (i=0; i<20; i++)
        for (j=0; j<50; j++)
            _nop_();
}

void
long_beep(void)
{
    uint16 i, j;
    for(i=0;i<500;i++){
        P1_0 = 1;
        for(j=0;j<50;j++) _nop_();
        P1_0 = 0;
        for(j=0;j<50;j++) _nop_();
    }
}

void 
two_beep(void)
{
    uint16 i,j;
    for(i=0; i< 150; i++){
        P1_0 = 1;
        for(j=0;j<100;j++)_nop_();
        P1_0 = 0;
        for(j=0;j<100;j++)_nop_();
    }
    for(i = 0; i < 300; i++);
    delay();
    for(i=0; i< 150; i++){
        P1_0 = 1;
        for(j=0;j<100;j++)_nop_();
        P1_0 = 0;
        for(j=0;j<100;j++)_nop_();
    }
}

static void
seg_disp(uint8 a, uint8 b, uint8 c, uint8 d)
{
    LED_PORT = seg_code[a];
    LED_COM1 = 0;
    delay();
    LED_COM1 = 1;
    LED_PORT = 0xff;

    LED_PORT = seg_code[b];
    LED_COM2 = 0;
    delay();
    LED_COM2 = 1;
    LED_PORT = 0xff;

    LED_PORT = seg_code[c];
    LED_COM3 = 0;
    delay();
    LED_COM3 = 1;
    LED_PORT = 0xff;

    LED_PORT = seg_code[d];
    LED_COM4 = 0;
    delay();
    LED_COM4 = 1;
    LED_PORT = 0xff;
}


void ledready(void)
{
    LED_PORT = seg_code[16];

    LED_COM1 = LED_COM2 = LED_COM3 = LED_COM4 = 0;
}

void passwdInput(void)
{
    uint8 key1=18, key2=18, key3=18, key4=18, key;
    uint8 pa, pb, pc, pd;

    //�����ȫ��
    LED_PORT = 0xff;
    LED_COM1 = LED_COM2 = LED_COM3 = LED_COM4 = 1;
    
   
    //��ȡ���������
    pa = iic2402_read(0x0)-1;
    pb = iic2402_read(0x1)-1;
    pc = iic2402_read(0x2)-1;
    pd = iic2402_read(0x3)-1;
    
   // seg_disp(pd, pc, pb, pa);
    
    while (1){
        do{
            key1 = read_key();
            seg_disp(18,18,18,18);
        }while(key1 > 10);
   
        if (key1 == 10){
            stat = ready;
            return ;
        }
      
        do{
            key2 = read_key();
            seg_disp(18, 18, 18, 16);
        }while(key2 > 10);
        if (key2 == 10){
            stat = ready;
            return ;
        }
  
        do{
            key3 = read_key();
            seg_disp(18, 18, 16, 16);
        }while(key3 > 10);
       
        if (key3 == 10){
            stat = ready;
            return ;
        }
        
        do{
            key4 = read_key();
            seg_disp(18, 16, 16, 16);
        }while(key4 > 10);
        
        if (key4 == 10){
            stat = ready;
            return ;
        }
        
        if((key1 == pa) && (key2 == pb) && (key3 == pc) && (key4 == pd)){
            two_beep();
            do{
                key = read_key();
                seg_disp(8,8,8,8);
            }while(key != 10);
            stat = ready;
            return ;
        }else{
            long_beep();
            do{
                key = read_key();
                seg_disp(17,17,17,17);
            }while(key != 10);
            stat = ready;
            return ;
        }
    }
}

void passwdChange(void)
{
    uint8 pa, pb, pc, pd;
    uint8 key1, key2, key3, key4, key;
    uint16 i = 0;
    
    LED_PORT = 0x00;
    LED_COM1 = LED_COM2 = LED_COM3 = LED_COM4 = 1;
    
    pa = iic2402_read(0x00)-1;
    pb = iic2402_read(0x01)-1;
    pc = iic2402_read(0x02)-1;
    pd = iic2402_read(0x03)-1;
    
    while(1){
         do{
            key1 = read_key();
            seg_disp(18,18,18,18);
        }while(key1 > 10);
   
        if (key1 == 10){
            stat = ready;
            return ;
        }
       
        do{
            key2 = read_key();
            seg_disp(18, 18, 18, key1);
        }while(key2 > 10);
        
        if (key2 == 10){
            stat = ready;
            return ;
        }
  
        do{
            key3 = read_key();
            seg_disp(18, 18, key2, key1);
        }while(key3 > 10);
       
        if (key3 == 10){
            stat = ready;
            return ;
        }
        
        do{
            key4 = read_key();
            seg_disp(18, key3, key2, key1);
        }while(key4 > 10);
        
        if (key4 == 10){
            stat = ready;
            return ;
        }
        
        if((key1 == pa) && (key2 == pb) && (key3 == pc) && (key4 == pd)){ //������ȷ
            two_beep();
            LED_PORT = 0x00;
            LED_COM1 = LED_COM2 = LED_COM3 = LED_COM4 = 1;
            
            do{
                key1 = read_key();
                seg_disp(8,8,8,8);
            }while(key1 > 10);
            
            if(key1 == 10){
                long_beep();
                stat = ready;
                return ;
            }
            
            do{
                key2 = read_key();
                seg_disp(18, 18, 18, key1);
            }while(key2 > 10);
            
            if(key2 == 10){
                stat = ready;
                return ;
            }
            
            do{
                key3 = read_key();
                seg_disp(18, 18, key2, key1);
            }while(key3 > 10);
            
            if(key3 == 10){
                stat = ready;
                return; 
            }
            
            do{
                key4 = read_key();
                seg_disp(18,key3, key2, key1);
            }while(key4 > 10);
            
            if(key4 == 10){
                stat = ready;
                return ;
            }
            
            do{
                key = read_key();
                seg_disp(key4, key3, key2, key1);
                
                if(key == 11){
                    iic2402_write(0x00, key1+1);
                    iic2402_write(0x01, key2+1);
                    iic2402_write(0x02, key3+1);
                    iic2402_write(0x03, key4+1);
                    two_beep();
                    stat = ready;
                    return ;
                }
                if(key == 10){
                    long_beep();
                    stat = ready;
                    return ;
                }
            }while(key > 11);
            return ;
        }else{  //�������
            long_beep();
            do{
                key = read_key();
                seg_disp(17,17,17,17);
            }while(key != 10);
            stat = ready;
            return ;
        }
    }
}

void main(void)
{
    //��������
    //��س�ʼ������

    uint8 key;
    
    while (1)
    {
        key = read_key();

        if (key == 13){
            stat = inputPasswd;
        }else if (key == 12){
            stat = changePasswd;
        }else{
            stat = ready;
        }
        
        switch (stat){

        case inputPasswd:
            passwdInput();
            break;
            
        case changePasswd:
            passwdChange();
            break;
            
        case ready:
        default:
             ledready();
             break;
        }
    }
}

//����������ļ���ʵ���жϴ��������Ҫ�ڰ���main�������ļ����������жϴ������
//����������ֱ�ӷ��ڰ���main�������ļ����߱�����main�������ļ�������ͷ�ļ���
//��������ʽΪ��void xxx_isr(void) __interrupt x
void INIT0_ISR(void) __interrupt 0
{
    //�ⲿ�ж�0�жϴ������
}

void TIMER0_ISR(void) __interrupt 1
{
    //��ʱ��0�жϴ������
}

void INIT1_ISR(void) __interrupt 2
{
    //�ⲿ�ж�1�жϴ������
}

void TIMER1_ISR(void) __interrupt 3
{
    //��ʱ��1�жϴ������
}

void SERIAL_ISR(void) __interrupt 4
{
    //�����жϴ������
    if (TI)  	//�����������
    {
        TI = 0;
        //�����Ĺ���
    }
    else
    {
        RI = 0;   //���յ�����
        //�����ݽ��д���
    }
}

void TIMER2_ISR(void) __interrupt 5
{
    //��ʱ��2�жϴ������
}
