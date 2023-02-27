/*xsh_updown.c - create two processes, p1 prints from 1 to 20, two numbers at a time, p2 froms from 101 and down, three numbers at a time*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_updown - shell command to create a process in the suspended state
--------------------------------------------------------------------------
*/
void upprocess(sid32), downprocess(sid32);

shellcmd xsh_updown(int nargs, char *args[]){
    sid32 sem1;
    if (nargs != 1){
        kprintf("Create command takes [0] arguments\n");
        return 0;
    }
    sem1=semcreate(2);
    resume(create(upprocess, 1024, 40, "upprocess", 1, sem1));
    resume(create(downprocess, 1024, 20, "downprocess", 1, sem1));
}

void upprocess(sid32 sem1){
    int i;
    for (i=0;i<=20;i++){
        wait(sem1);
        kprintf("up   %d \n",i);
        
    }
}

void downprocess(sid32 sem1){
    int i,c;
    c=0;
    for(i=101;i>0;i--){
        kprintf("down %d \n",i);
        c++;
        if(c%3==0)
        {
            signaln(sem1, 2);
        }
    }
}
