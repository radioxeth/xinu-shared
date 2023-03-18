/* xsh_sndcrypto.c - xsh_sndcrypto */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include "crypto_aead.h"
#include "api.h"


int send_encrypted_msg(pid32, char*, int);

/*------------------------------------------------------------------------
 * xsh_sndcrypto - send an encrypted message to a pid
 *------------------------------------------------------------------------
 */
shellcmd xsh_sndcrypto(int nargs, char *args[])
{
    pid32 pid;
    int32 i;
    char *msg;
    int msglen;
    int result;
    if (nargs != 3) {
        fprintf(stderr,"use is sndmsg [pid] [msg]\n");
        return 1;
    }
    else {
        pid = atoi(args[1]);
        msg = args[2];
    }
    for(i=0; i < MAX_MESSAGE_LENGTH; i++){
        if(msg[i] == NULL){
            msglen = i;
            break;
        }
    }
    result=send_encrypted_msg(pid, msg, msglen);
    kprintf("encrypted result %d\n",result);
}

int send_encrypted_msg(pid32 pid, char *msg, int msglen){
    unsigned char n[CRYPTO_NPUBBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char k[CRYPTO_KEYBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char a[16] = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char c[32], h[32], t[32];
    unsigned long long alen = 8;
    unsigned long long mlen = 8;
    unsigned long long clen = CRYPTO_ABYTES;
    int mi,result;
    unsigned long long i;
    
    i=0;
    for (mi=0;mi<msglen;mi++){
        m[i]=msg[mi];
        i++;
    }
    print('m', m, mlen);
    printf(" -> \n");
    result=0;
    result |= crypto_aead_encrypt(c, &clen, m, mlen, a, alen, (void*)0, n, k);
    print('s', c, clen);
    printf(" -> \n");
    for(i=0; i<=clen; i++) {
        if(i==clen){
            if (sendk(pid, '\0') == SYSERR){
                kprintf("SYSERR NULL\n");
            }
            kprintf("----END OF SEND----\n");
        }else{
            if (sendk(pid, c[i]) == SYSERR){
                kprintf("SYSERR %c\n",c[i]);
            }
        }
    }
    // for(i=0; i<=mlen && i<=msglen; i++) {
    //     if(i==mlen||i==msglen){
    //         if (sendk(pid, '\0') == OK){
    //             kprintf("OK NULL\n");
    //         } else {
    //             kprintf("SYSERR NULL\n");
    //         }
    //     }else{
    //         printf("m[%d]=%c ",mi,m[i]);
    //         if (sendk(pid, m[i]) == OK){
    //             kprintf("OK\n");
    //         } else {
    //             kprintf("SYSERR\n");
    //         }    
    //     }
    // }
    return result;
}

// int send_encrypted_msg(pid32 pid, char *msg, int msglen){
//     unsigned char n[CRYPTO_NPUBBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
//     unsigned char k[CRYPTO_KEYBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
//     unsigned char a[16] = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
//     unsigned char m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//     unsigned char c[32], h[32], t[32];
//     unsigned long long alen = 8;
//     unsigned long long mlen = 8;
//     unsigned long long clen = CRYPTO_ABYTES;
//     int result = 0;
//     int mi;
//     for (mi=0;mi<msglen;mi++){
//         m[mi]=msg[mi];
//     }
//     print('k', k, CRYPTO_KEYBYTES);
//     printf(" ");
//     print('n', n, CRYPTO_NPUBBYTES);
//     printf("\n");
//     print('a', a, alen);
//     printf(" ");
//     print('m', m, mlen);
//     printf(" -> ");
//     result |= crypto_aead_encrypt(c, &clen, m, mlen, a, alen, (void*)0, n, k);
//     print('c', c, clen - CRYPTO_ABYTES);
//     printf(" ");
//     print('t', c + clen - CRYPTO_ABYTES, CRYPTO_ABYTES);
//     printf(" -> ");
//     result |= crypto_aead_decrypt(m, &mlen, (void*)0, c, clen, a, alen, n, k);
//     print('a', a, alen);
//     printf(" ");
//     print('m', m, mlen);
//     int i;
//     for(i=0;i<mlen;i++){
//     printf("m[%d] %c ",i, (char)m[i]);
//     }
//     printf("\n");
//     int j;
//     for(i=0;i<clen;i++){
//     printf("c[%d] %c ",j, (char)c[j]);
//     }
//     printf("\n");
//     return 1;
// }