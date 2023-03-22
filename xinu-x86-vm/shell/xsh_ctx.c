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
    if (nargs<1 || nargs>2){
        kprintf("Create command takes [0] or [1 - reprio_type(0 or 1)] argument\n");
        return 0;
    }else if(nargs==1){
        reprio_type=0;
    }else{
        reprio_type=atoi(args[1]);
    }
    printf("reprio_type (%d)\n",reprio_type);
    resume(create(p1, 1024, 20, "p1", FALSE, 0));
    resume(create(p2, 1024, 20, "p2", FALSE, 0));
    resume(create(pstarve, 1024, 5, "pstarve1", TRUE, 0));
    return 1;
}

void p1(){
    while(TRUE);
}

void p2(){
    while(TRUE);
}

void pstarve(void){
    kprintf("pstarve ran with PID %d!\n",getpid());
}