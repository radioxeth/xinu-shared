/*xsh_createctx.c - xshcreatectx*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>

void p1(void);
void p2(void);
void pstarve(void);

/*
--------------------------------------------------------------------------
xsh_createctx - shell command to create a new process with a specific priority
--------------------------------------------------------------------------
*/
shellcmd xsh_ctx(int nargs, char *args[]){
    pri16 priority;           /* priority of the new process */
    if (nargs!=1){
        kprintf("Create command takes [0] argument\n");
        return 0;
    }
    if(priority < 0){
        kprintf("please enter a digit priority greater than 0\n");
        return 0;
    }
    priority=20;
    resume(create(p1, 1024, 20, "p1", FALSE, 0));
    resume(create(p2, 1024, 20, "p2", FALSE, 0));
    sleepms(1000);
    resume(create(pstarve, 1024, 5, "pstarve", TRUE, 0));
    return 1;
}

void p1(){
    while(TRUE);
}

void p2(){
    while(TRUE);
}

void pstarve(void){
    while(TRUE){
        kprintf("pstarve ran with PID %d!\n",getpid());
    }
    
}