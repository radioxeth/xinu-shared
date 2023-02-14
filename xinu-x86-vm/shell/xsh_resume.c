/*xsh_bufferprint.c - xshbufferprint*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_bufferprint - shell command to print 1 to n using a buffer
--------------------------------------------------------------------------
*/

shellcmd xsh_resume(int nargs, char *args[]){
    pid32 pid;
    if (nargs>2||nargs<=1){
        kprintf("Create command takes [1] argument, process number\n");
        return 0;
    } else if(nargs==2){
        pid=  atoi(args[1]);
    }
    if(isbadpid(pid)==0){
        resume(pid);
    }
    return 1;
}