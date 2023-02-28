/*xsh_createsleep.c - xshcreatesleep*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>

void sleepinfinite(void);

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
    pid = create(sleepinfinite, 1024, 20, "sleepinfinite", 0);
    resume(pid);
    kprintf("PID: %d\n",pid);
    return 1;
}

void sleepinfinite(void){
    sleep(10);
    while(TRUE);
}