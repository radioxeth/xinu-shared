/* xsh_sndcrypto.c - xsh_sndcrypto */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include "crypto_aead.h"
#include "api.h"


int send_encrypted_msg(unsigned char* msg, pid32 pid);
void init_buffer(unsigned char *,unsigned long long );

/*------------------------------------------------------------------------
 * xsh_sndcrypto - send an encrypted message to a pid
 *------------------------------------------------------------------------
 */
shellcmd xsh_sndcrypto(int nargs, char *args[])
{
    pid32 pid;
    int32 i;
    char *msg;
    unsigned char umsg[MAX_MESSAGE_LENGTH];
    int result;
    if (nargs != 3) {
        fprintf(stderr,"use is sndmsg [pid] [msg]\n");
        return 1;
    }
    else {
        pid = atoi(args[1]);
        msg = args[2];
    }
    for(i=0;i<MAX_MESSAGE_LENGTH;++i){
        if(msg[i]!=NULL){
            umsg[i]=msg[i];
        }
        
    }
    result = send_encrypted_msg(umsg,pid);
    kprintf("result %d\n",result);
    
}


int send_encrypted_msg(unsigned char *msg, pid32 pid){
    unsigned char nonce[CRYPTO_NPUBBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char key[CRYPTO_KEYBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char ad[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char m[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char ct[32], h[32], t[32];
    unsigned long long adlen = 8;
    unsigned long long mlen = 8;
    unsigned long long clen = CRYPTO_ABYTES;
    int result=0;
    // init_buffer(msg, sizeof(msg));
    kprintf("init buffer msg(%s)\n", msg);
    result |= crypto_aead_encrypt(ct, &clen, msg, mlen, ad, adlen, NULL, nonce, key);
    kprintf("sending PID(%4d) msg(%s) encrypted(%s) ", pid, msg, ct);
    if (sendkcrypto(pid, ct) == OK){
        kprintf("OK\n");
    } else {
        kprintf("SYSERR\n");
    }
    return result;
}

void init_buffer(unsigned char *buffer, unsigned long long numbytes) {
  unsigned long long i;
  for (i = 0; i < numbytes; i++) buffer[i] = (unsigned char)i;
}
