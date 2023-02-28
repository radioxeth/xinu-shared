/*xsh_createsus.c - create an indefinite process*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_createsus - shell command to create a process in the suspended state
--------------------------------------------------------------------------
*/
void process1(void);

shellcmd xsh_createsus(int nargs, char *args[]){
    pid32 pid;
    pri16 prio;
    if (nargs > 2){
        kprintf("Create command takes [1] arguments, the priority\n");
        return 0;
    }else if (nargs==2){
        prio=atoi(args[1]);
    }else{
        prio=20;
    }
    pid = create(process1, 1024, prio, "myprocess", 0);
    kprintf("PID: %d\n", pid);
    return pid;
}

void process1(void){
    while(TRUE);
}