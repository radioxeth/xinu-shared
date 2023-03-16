/* sendkcrypto.c - sendkcrypt */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  sendkcrypto  -  pass k messages to a process and start recipient if waiting, ecnrypt the message
 *------------------------------------------------------------------------
 */
syscall	sendkcrypto(
	  pid32		pid,	        	/* ID of recipient process	*/
	  unsigned char*     msg		/* contents of message		*/
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
	if ((prptr->prstate == PR_FREE) || prptr->prhasmsg) {
		restore(mask);
		return SYSERR;
	}
    
	prptr->prmsgbuff = msg;		/* deliver message		*/
	prptr->prhasmsg = TRUE;		/* indicate message is waiting	*/

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



