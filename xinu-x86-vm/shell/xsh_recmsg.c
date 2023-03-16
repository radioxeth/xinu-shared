/* xsh_remsg.c - xsh_remsg */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include "crypto_aead.h"
#include "api.h"

void receiver(void);
// int decrypt_msg(unsigned char*);
/*------------------------------------------------------------------------
 * xsh_remsg - receive and print a message
 *------------------------------------------------------------------------
 */
shellcmd xsh_recmsg(int nargs, char *args[])
{

    /* Insure no arguments were passed */

    if (nargs > 1) {
        fprintf(stderr,"use is remsg\n");
        return 1;
    }
    resume(create(receiver, 1024, 15, "receiver", 0));
    return 0;
}

void receiver(void)
{
    int i;
    unsigned long long mlen = 8;
    pid32 pid = getpid();

    kprintf("PID(%d) is receiving\n",pid);
    unsigned long long mi=0;
    unsigned char m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    while(TRUE){
        unsigned char msg = receivek();
        kprintf("PID(%d) received msg(%c)\n", pid, msg);
        if(msg=='\0'){
            print('r',m,mi-1);
            printf(" -> \n");
            for(i=0;i<16;i++){
                m[i]=0;
            }
            mi=0;
        }else{
            m[mi]=msg;
            mi++;    
        }
        
    }
}
