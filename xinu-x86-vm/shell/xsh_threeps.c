/*xsh_bufferprint.c - xshbufferprint*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_bufferprint - shell command to print 1 to n using a buffer
--------------------------------------------------------------------------
*/
void p1(void);
void p2(void);
void p3(void);

shellcmd xsh_threeps(int nargs, char *args[]){
    pri16 prio1, prio2, prio3;
    if (nargs>=2){
        kprintf("Create command takes [1] argument, process number\n");
        return 0;
    } else if (nargs==1){
        processNum = 0;
    } else if(nargs==2){
        processNum = atoi(args[1]);
    }
    create(p1,1024,20,"p1",0);
    create(p2,1024,20,"p2",0);
    create(p3,1024,20,"p3",0);
    return 1;
}

void p1(void){
    while(TRUE);
}
void p2(void){
    while(TRUE);
}
void p3(void){
    while(TRUE);
}