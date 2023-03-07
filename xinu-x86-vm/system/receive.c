/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
syscall  receive(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	*msgs;			/* message to return		*/
	int32 i = 0;

	mask = disable();
	prptr = &proctab[currpid];
	
	kprintf("In receieve, the currpid is %d \n",currpid); 
	kprintf("Message count = %d \n", prptr->msg_count);
	
	// only block when the process has no messages
	if (prptr->msg_count == 0) {
		kprintf("BUFFER EMPTY \n");
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	
	// loop through process messages 
	while(prptr->msg_count > 0)
	{	
		msgs[i] = prptr->prmsg1[i];		/* Retrieve message		*/
		prptr->msg_count--;	
		i++;
		kprintf("\nReceiver%d has received the following Message :%d from sender",currpid,msgs[i]);
	}	

	prptr->prhasmsg = FALSE;	/* reset message flag		*/
	restore(mask);
	return OK;
}
