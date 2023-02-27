/*xsh_resume.c - resume a suspended process into the ready state*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_resume - shell command to print 1 to n using a buffer
--------------------------------------------------------------------------
*/

shellcmd xsh_resume(int nargs, char *args[]){
    pid32 pid;
    if (nargs != 2){
        kprintf("Resume command takes [1] argument, a pid\n");
        return 0;
    }
    pid = atoi(args[1]);
    return resume(pid);
}