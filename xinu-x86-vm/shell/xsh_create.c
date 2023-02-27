/*xsh_create.c - create an indefinite process*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_create - shell command to create a process in the suspended state
--------------------------------------------------------------------------
*/
void process1(void);

shellcmd xsh_create(int nargs, char *args[]){
    pid32 pid;
    if (nargs != 1){
        kprintf("Create command takes [0] arguments\n");
        return 0;
    }
    pid = create(process1, 1024, 20, "myprocess", 0);
    return pid;
}

void process1(void){
    while(TRUE);
}
