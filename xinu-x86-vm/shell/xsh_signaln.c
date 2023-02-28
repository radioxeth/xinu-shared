/*xsh_signaln.c - xsh_signaln*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*
--------------------------------------------------------------------------
xsh_wait - shell command to create a new process and wait on it
--------------------------------------------------------------------------
*/
shellcmd xsh_signaln(int nargs, char *args[]){
    int32 n;           // n the number of semaphores to release
    if (nargs>2){
        kprintf("wait command takes [1] arguments.\n");
        return 0;
    }else{
        n = atoi(args[1]);
    }
    signaln(gsem,n);
    return 1;
}