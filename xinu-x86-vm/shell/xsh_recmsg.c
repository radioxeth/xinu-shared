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
    pid32 pid = getpid();

    kprintf("PID(%d) is receiving\n",pid);
    unsigned char c[32];
    unsigned long long mi   = 0;
    int result;
    while(TRUE){
        
        unsigned char msg = receivek();
        if (mi==CRYPTO_ABYTES) {
            unsigned char n[CRYPTO_NPUBBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
            unsigned char k[CRYPTO_KEYBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
            unsigned char a[16] = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
            unsigned char m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            
            unsigned long long alen = 8;
            unsigned long long mlen = 8;
            
            unsigned long long clen = CRYPTO_ABYTES+mlen;
            print('r', c, clen);
            printf(" -> \n");
            result=0;
            result |= crypto_aead_decrypt(m, &mlen, (void*)0, c, clen, a, alen, n, k);
            printf("decrypted message result (%d)\n",result);
            print('m', m, mlen);
            printf(" -> \n");
            mi=0;
            kprintf("----END OF REC----\n");
        } else {
            c[mi]=msg;
            mi++;
        }
        // kprintf("PID(%d) received msg(%c)\n", pid, msg);
        // if(msg=='\0'){
        //     print('r', m, mi);
        //     printf(" -> \n");
        //     for(i=0;i<16;i++){
        //         m[i]=0;
        //     }
        //     mi=0;
        // }else{
        //     m[mi]=msg;
        //     mi++;    
        // }
        
    }
}
