/* resched.c - resched */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* ptr to table entry for old process	*/
	struct procent *ptnew;	/* ptr to table entry for new process	*/

	struct	procent	*prptr;		/* pointer to process		*/
	int32	pid;			/* index into proctabl		*/

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* process remains running */
		
		if (ptold->prprio > firstkey(readylist) && ptold->prreprio==FALSE) {
			return;
		}
		else if(ptold->prreprio==TRUE) {
			ptold->prprio = ptold->progprio;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
	
	/* check for */
	for (pid = 0; pid < NPROC; pid++) {
		prptr = &proctab[pid];
		if(prptr->prstate == PR_READY && prptr->prreprio==TRUE) {
			kprintf("%3d %-16s %4d\n",
			pid, prptr->prname, prptr->prprio);
			prptr->prprio++;
			getitem(pid);
			insert(pid, readylist, prptr->prprio);
			break;
		}
	}

	/* Old process returns here when resumed */

	return;
}
