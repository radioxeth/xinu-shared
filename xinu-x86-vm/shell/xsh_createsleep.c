/*xsh_createsleep.c - xshcreatesleep*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>

void processn(int32ps);
/*
--------------------------------------------------------------------------
xsh_createsleep - shell command to create a new process with a specific priority
--------------------------------------------------------------------------
*/
shellcmd xsh_createsleep(int nargs, char *args[]){
    int scheduletype;
    if (nargs!=2){
        kprintf("Create command takes [1] argument, the sleep type.\n");
        kprintf("[0] for priority based\n");
        kprintf("[1] for first come, first served\n");
        return 0;
    }
    scheduletype=atoi(args[1]);
    if(scheduletype<0||scheduletype>1){
        kprintf("[0] for priority based\n");
        kprintf("[1] for first come, first served\n");
        return 0;
    }
    if (scheduletype==0) {
        kprintf("PRIORITY BASED\n");
        gschedtype = PRIORITY_BASED;
    } else {
        kprintf("FIFO BASED\n");
        gschedtype = FIFO_BASED;
    }
    resume(create(processn, 1024, 5, "process2", 1, 2));
	resume(create(processn, 1024, 10, "process3", 1, 3));
	resume(create(processn, 1024, 20, "process4", 1, 4)); 
    return 0;
}

void processn(int32 n){
    int i;
	printf("Process %d PID: %d\n", n, getpid());
    sleep(2);
    for(i=0;i<10;++i){
        kprintf("Process %d is running\n", n);
    }
}