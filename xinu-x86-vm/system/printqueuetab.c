/*printqueuetab.c - prints the active processes and queues of the queue table*/

#include <xinu.h>

status printqueuetab(void){
    int i=0;
    // Print the processes 0 to NPROC-1
    printf("\n");
    printf("|pid   |qkey  |qprev |qnext |\n");
    printf("|---------------------------|\n");
	while (i<NPROC){
		if(isbadpid(i)==0) {
			printf("|%6d|%6d|%6d|%6d|\n",i,queuetab[i].qkey,queuetab[i].qprev,queuetab[i].qnext);
		}
		i++;
	}
	// Here is the theoretical boundary
    printf("|---------------------------|\n");
    // iterate to the number of queue entries
	while (i<NQENT){
		if(nonempty(i) && firstid(i)!=-1){ // if the queue is not empty and the first id is not null/-1
			printf("|%6d|MAXKEY|%6d|%6d|\n",i,queuetab[i].qprev,queuetab[i].qnext);
			i++;
			printf("|%6d|MINKEY|%6d|%6d|\n",i,queuetab[i].qprev,queuetab[i].qnext);
		}
		i++;
	}
    printf("|---------------------------|\n");
    return(OK);
}