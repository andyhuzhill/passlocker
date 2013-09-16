
#include "key.h"

static void delay(void)
{
    int i;
    for(i=0;i<15;i++)
        _nop_();
}

/*
 * É¨Ãè·¨¶Á¾ØÕó¼üÅÌ
 */
uint8
read_key(void)
{
    uint8 tmp;
    
    KEY_PORT = 0xf0;
    tmp = KEY_PORT;
    
    if(tmp != 0xf0){
        delay();
        if(tmp != 0xf0){
            KEY_PORT = 0xfe;
            tmp = KEY_PORT;
            switch(tmp){
                case (0xee): while(KEY_PORT == tmp); return (-1);break;
                case (0xde): while(KEY_PORT == tmp); return (1);break;
                case (0xbe): while(KEY_PORT == tmp); return (4);break;
                case (0x7e): while(KEY_PORT == tmp); return (7);break;
                default:
                    break;
            }
            
            KEY_PORT = 0xfd;
            tmp = KEY_PORT;
            switch(tmp){
                case (0xed): while(KEY_PORT == tmp); return (0);break;
                case (0xdd): while(KEY_PORT == tmp); return (2);break;
                case (0xbd): while(KEY_PORT == tmp); return (5);break;
                case (0x7d): while(KEY_PORT == tmp); return (8);break;
                default:
                    break;
            }
            
            KEY_PORT = 0xfb;
            tmp = KEY_PORT;
            switch(tmp){
                case (0xeb): while(KEY_PORT == tmp); return (-1);break;
                case (0xdb): while(KEY_PORT == tmp); return (3);break;
                case (0xbb): while(KEY_PORT == tmp); return (6);break;
                case (0x7b): while(KEY_PORT == tmp); return (9);break;
                default:
                    break;
            }
            
            KEY_PORT = 0xf7;
            tmp = KEY_PORT;
            switch(tmp){
                case (0xe7): while(KEY_PORT == tmp); return (10);break;
                case (0xd7): while(KEY_PORT == tmp); return (11);break;
                case (0xb7): while(KEY_PORT == tmp); return (12);break;
                case (0x77): while(KEY_PORT == tmp); return (13);break;
                default:
                	return -1;
                    break;
            }
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}
