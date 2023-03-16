/* receivek.c - receivek */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receivek  -  wait for k messages and return the messages to the caller
 *------------------------------------------------------------------------
 */
unsigned char * receivek(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	unsigned char*	msg;			/* message to return		*/
	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* block until message arrives	*/
	}
	msg = prptr->prmsgbuff;		/* retrieve message		*/
	prptr->prhasmsg = FALSE;	/* reset message flag		*/
	restore(mask);
	return msg;
}
