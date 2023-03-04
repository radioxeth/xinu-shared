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
    pid32 pid;                /*process id of the new process*/
    if (nargs>=2){
        kprintf("Create command takes [0] arguments.\n");
        return 0;
    }
    resume(create(processn, 1024, 5, "process2", 1, 2));
	resume(create(processn, 1024, 10, "process3", 1, 3));
	resume(create(processn, 1024, 20, "process4", 1, 4));
    
    return 1;
}

void processn(int32 n){
	printf("Process 2 PID: %d\n",getpid());
    while(TRUE){
        sleep(2);
        kprintf("Process 2 is running\n");
    }
}