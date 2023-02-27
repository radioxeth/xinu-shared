/*xsh_suspend.c - resume a suspended process into the ready state*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_suspend - shell command to suspend a process that is not free
--------------------------------------------------------------------------
*/

shellcmd xsh_suspend(int nargs, char *args[]){
    pid32 pid;
    if (nargs != 2){
        kprintf("Suspend command takes [1] argument, a valid pid\n");
        return 0;
    }
    pid = atoi(args[1]);
    suspend(pid);
    return 1;
}