/*xsh_wait.c - xsh_wait*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>

void waiter(void);

/*
--------------------------------------------------------------------------
xsh_wait - shell command to create a new process and wait on it
--------------------------------------------------------------------------
*/
shellcmd xsh_wait(int nargs, char *args[]){
    pid32 pid;                /*process id of the new process*/
    if (nargs>=2){
        kprintf("wait command takes [0] arguments.\n");
        return 0;
    }
    pid = create(waiter, 1024, 20, "newprocess", 0);
    kprintf("PID: %d\n", pid);
    resume(pid);
    return 1;
}

void waiter(void){
    wait(gsem);
    while(TRUE){};
}