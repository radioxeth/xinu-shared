/* xsh_recmsg.c - xsh_recmsg */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include "crypto_aead.h"
#include "api.h"

void receiver(void);
int decrypt_msg(unsigned char*);
/*------------------------------------------------------------------------
 * xsh_recmsg - receive and print a message
 *------------------------------------------------------------------------
 */
shellcmd xsh_recmsg(int nargs, char *args[])
{

    /* Insure no arguments were passed */

    if (nargs > 1) {
        fprintf(stderr,"use is recmsg\n");
        return 1;
    }
    resume(create(receiver, 1024, 15, "receiver", 0));
    return 0;
}

void receiver(void)
{
    unsigned char* msg;
    pid32 pid = getpid();
    int result;
    kprintf("PID(%d) is receiving\n",pid);
    while(TRUE){
        msg = receivek();
        kprintf("PID(%d) received msg(%s)\n", pid, msg);
        result=decrypt_msg(msg);
        kprintf("result: %d\n",result);
    }
}

int decrypt_msg(unsigned char* msg){
    unsigned char nonce[CRYPTO_NPUBBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char key[CRYPTO_KEYBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char ad[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    // unsigned char m[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char ct[32], h[32], t[32];
    unsigned long long adlen = 8;
    unsigned long long mlen = 8;
    unsigned long long clen = CRYPTO_ABYTES;
    unsigned char* dmsg;
    int result=0;    
    result |= crypto_aead_decrypt(msg, &mlen, NULL, ct, clen, ad, adlen, nonce, key);
    // kprintf("ad (%s), adlen (%d)\n", ad, adlen);
    kprintf("decrypted msg (%s), mlen (%d)\n", ct, mlen);
    return result;
}
