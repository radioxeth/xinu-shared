/* xsh_demo.c - xsh_demo */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include "crypto_aead.h"
#include "api.h"


// int demo(char*, int);

/*------------------------------------------------------------------------
 * xsh_demo - demo ascon encryption
 *------------------------------------------------------------------------
 */
shellcmd xsh_demo(int nargs, char *args[])
{
    int32 i;
    char *msg;
    int msglen;
    // int result;
    if (nargs != 2) {
        fprintf(stderr,"use is demo [msg]\n");
        return 1;
    }
    else {
        msg = args[1];
    }

    for(i=0; i < MAX_MESSAGE_LENGTH; i++){
        if(msg[i] == NULL){
            msglen = i;
            break;
        }
    }
    unsigned char n[CRYPTO_NPUBBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char k[CRYPTO_KEYBYTES] = {0, 1, 2,  3,  4,  5,  6,  7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char a[16] = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char c[32], h[32], t[32];
    unsigned long long alen = 8;
    unsigned long long mlen = 8;
    unsigned long long clen = CRYPTO_ABYTES;
    int result = 0;
    int mi;

    for (mi=0;mi<msglen;mi++){
        m[mi]=msg[mi];
    }
    kprintf("plaintext: %s\n", m);
    print('m', m, mlen);
    printf(" -> \n");
    result |= crypto_aead_encrypt(c, &clen, m, mlen, a, alen, (void*)0, n, k);
    print('c', c, clen - CRYPTO_ABYTES);
    printf(" ");
    print('t', c + clen - CRYPTO_ABYTES, CRYPTO_ABYTES);
    printf(" -> \n");
    result |= crypto_aead_decrypt(m, &mlen, (void*)0, c, clen, a, alen, n, k);
    print('m', m, mlen);
    printf(" -> \n");
    kprintf("plaintext: %s\n", m);
}

// int demo(char *msg, int msglen){
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
//         kprintf("m[%d] %c ",mi, m[mi]);
//     }
//     print('m', m, mlen);
//     printf(" -> ");
//     result |= crypto_aead_encrypt(c, &clen, m, mlen, a, alen, (void*)0, n, k);
//     kprintf("ciphertext:\n");
//     print('c', c, clen - CRYPTO_ABYTES);
//     printf(" ");
//     print('t', c + clen - CRYPTO_ABYTES, CRYPTO_ABYTES);
//     printf(" -> ");
//     result |= crypto_aead_decrypt(m, &mlen, (void*)0, c, clen, a, alen, n, k);
//     kprintf("plaintext:\n");
//     print('m', m, mlen);
//     printf(" -> ");
//     for(mi=0;mi<msglen;mi++){
//         kprintf("m[%d] %c ",mi, m[mi]);
//     }
//     printf("\n");
//     return 1;
// }