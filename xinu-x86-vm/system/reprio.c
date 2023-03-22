#include <xinu.h>

/*
	reprioritize the tasks that can be reprioritized
*/
void reprio(void){
	struct	procent	*prptr;		/* pointer to process		*/
	int32	pid;			/* index into proctabl		*/
	for (pid = 0; pid < NPROC; pid++) {
		prptr = &proctab[pid];
		if(prptr->prstate == PR_READY && prptr->prreprio==TRUE) {
			kprintf("%3d %-16s %4d at time %d\n", pid, prptr->prname, prptr->prprio, clktime);
			prptr->prprio++;
			getitem(pid);
			insert(pid, readylist, prptr->prprio);
			break;
		}
	}
	return;
}

/* 
	reprio context switch
	call reprio if the reprio_type==0 (on contex switch) 
*/
void reprioctx(void) {
	if(reprio_type==0){
		reprio();
	}
}

/*
	reprio timed
	call reprio if the reprio_type==1 (every second)
*/
void repriotmd(void) {
	if((reprio_type==1) && ((clktime-nowtime)>=1)) // reprio if time difference is greater than 1
	{
		reprio();
		nowtime = clktime;
	}
}