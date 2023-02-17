/*xsh_create.c - xshcreate*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_create - shell command to display Alice and Bob's convo
--------------------------------------------------------------------------
*/
shellcmd xsh_create(int nargs, char *args[]){
    pri16 priority;           /* priority of the new process */
    if (nargs>2){
        kprintf("Create command takes [1] argument, the priority of the new process.\n");
        return 0;
    } else if (nargs==1){
        priority = 20;
    } else if(nargs==2){
        priority = atoi(args[1]);
    }
    if(priority < 0){
        kprintf("please enter a digit priority greater than 0\n");
        return 0;
    }
    createInfinite(priority);
    return 1;
}