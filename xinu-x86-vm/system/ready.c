/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid,		/* ID of process to make ready	*/
	  bool8		resch		/* reschedule afterward?	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return(SYSERR);
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	if ( gschedtype == PRIORITY_BASED ) {
		insert(pid, readylist, prptr->prprio); //insert for priority based
	} else if( gschedtype == FIFO_BASED ) {
		enqueue(pid, readylist);               //enqueue for fifo
	} else {
		insert(pid, readylist, prptr->prprio); // default to priority based
	}
	
	
	if (resch == RESCHED_YES) {
		resched();
	}
	return OK;
}
