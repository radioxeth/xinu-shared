/* receivek.c - receivek */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receivek  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
unsigned char receivek(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->startptr == -1) {
		prptr->prstate = PR_RECV;
		resched();		/* block until message arrives	*/
	}
    prptr->startptr++;
	msg = prptr->prmsgbuff[prptr->startptr];		/* retrieve message		*/
	if(prptr->startptr==prptr->endptr){
		prptr->startptr = -1;
		prptr->endptr   = -1;
	}
	if(prptr->startptr > MAX_MESSAGE_LENGTH || prptr->endptr>MAX_MESSAGE_LENGTH){
		prptr->startptr = -1;
		prptr->endptr   = -1;
	}
	restore(mask);
	return msg;
}