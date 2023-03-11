/* receivek.c - receivek */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receivek  -  wait for k messages and return the messages to the caller
 *------------------------------------------------------------------------
 */
umsg32	receivek(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->msgcount == 0) {
		prptr->prstate = PR_RECV;
		resched();		/* block until message arrives	*/
	}
    prptr->msgcount--;
	msg = prptr->prmsgbuff[prptr->msgcount];		/* retrieve message		*/

	// prptr->prhasmsg = FALSE;	/* reset message flag		*/
	restore(mask);
	return msg;
}
