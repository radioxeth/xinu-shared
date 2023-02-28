/*xsh_resumen.c - resume a suspended n process into the ready state*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_resumen - shell command to resume n process ids
--------------------------------------------------------------------------
*/

shellcmd xsh_resumen(int nargs, char *args[]){
    pid32 pid;
    int i;
    if (nargs < 2){
        kprintf("Resume command takes [n] argument, the pids to resume\n");
        return 0;
    }
    i=1;
    while(atoi(args[i]) != -1) {
        pid = atoi(args[i]);
        resume(pid);
        i++;
    }
    
    return 1;
}