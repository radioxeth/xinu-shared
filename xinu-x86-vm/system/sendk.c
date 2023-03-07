/* send.c - send */

#include <xinu.h>

extern int32 max_msg;

/*------------------------------------------------------------------------
 *  send  -  pass a message to a process and start recipient if waiting
 *  modified to accept multiple messages
 *------------------------------------------------------------------------
 */
syscall	sendk(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32*	msgs,		/* contents of messages		*/
	  int32 num_messages
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	int i;

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	prptr = &proctab[pid];

	// loop through messages 
	for(i=0;i< num_messages;i++)
	{		
		// check for an overflowed process message buffer
		// max_msg defined in main as global var	
		if (prptr->msg_count == max_msg)
		{
			kprintf("Too many messages!!!\n");
			return SYSERR;
		}
		// send current message to process message buffer
		// also increment process message count
		else
		{
			kprintf("\nSender %d is sending the following message :%d to receiver %d \n",currpid,msgs[i],pid);			
			prptr->prmsg1[i] = msgs[i];
			prptr->msg_count++;
		}
	}	

	prptr->prhasmsg = TRUE;		/* indicate message is waiting	*/

	/* If recipient waiting or in timed-wait make it ready */

	//if (prptr->prstate == PR_RECV) {
	//	ready(pid, RESCHED_YES);
	//} else if (prptr->prstate == PR_RECTIM) {
	//	unsleep(pid);
	//	ready(pid, RESCHED_YES);
	//}
	restore(mask);		/* restore interrupts */
	return OK;
}
