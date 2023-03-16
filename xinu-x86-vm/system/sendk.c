/* sendk.c - sendk */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  sendk  -  pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendk(
	  pid32		pid,		/* ID of recipient process	*/
	  unsigned char	msg		/* contents of message		*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if ((prptr->prstate == PR_FREE) || prptr->endptr >= (MAX_MESSAGE_LENGTH+1)) {
		restore(mask);
		return SYSERR;
	}
	// if(prptr->endptr=-1 && prptr->startptr==-1)
	prptr->endptr++;                            /* increase message count */
	prptr->prmsgbuff[prptr->endptr] = msg;		/* deliver message		*/
	// if(prptr->startptr > MAX_MESSAGE_LENGTH || prptr->endptr>MAX_MESSAGE_LENGTH){
	// 	prptr->startptr = -1;
	// 	prptr->endptr   = -1;
	// }
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