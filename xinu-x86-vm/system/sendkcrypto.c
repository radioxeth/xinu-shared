/* sendkcrypto.c - sendkcrypt */

#include <xinu.h>
#include "crypto_aead.h"
#include "api.h"

int encrypt(umsg32);
void init_buffer(unsigned char *,unsigned long long);


/*------------------------------------------------------------------------
 *  sendkcrypto  -  pass k messages to a process and start recipient if waiting, ecnrypt the message
 *------------------------------------------------------------------------
 */
syscall	sendkcrypto(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* contents of message		*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
    int encrypted;
	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if ((prptr->prstate == PR_FREE) || prptr->msgcount >= NMSG) {
		restore(mask);
		return SYSERR;
	}

    encrypted=encrypt(msg);

	prptr->prmsgbuff[prptr->msgcount] = msg;		/* deliver message		*/
    prptr->msgcount++;
	// prptr->prhasmsg = TRUE;		/* indicate message is waiting	*/

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid, RESCHED_YES);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid, RESCHED_YES);
	}
	restore(mask);		/* restore interrupts */
	return OK;
}

int encrypt(umsg32 msg){
    int encrypted;
    unsigned char key[CRYPTO_KEYBYTES];
    unsigned char nonce[CRYPTO_NPUBBYTES];
    unsigned char msg[MAX_MESSAGE_LENGTH];
    unsigned char ad[MAX_ASSOCIATED_DATA_LENGTH];
    unsigned char ct[MAX_MESSAGE_LENGTH + CRYPTO_ABYTES];
    unsigned long long mlen, adlen;
    unsigned long long clen;
    encrypted = crypto_aead_encrypt(ct, &clen, msg, mlen, ad, adlen,
                        NULL, nonce, key);
}

void init_buffer(unsigned char *buffer, unsigned long long numbytes) {
  unsigned long long i;
  for (i = 0; i < numbytes; i++) buffer[i] = (unsigned char)i;
}