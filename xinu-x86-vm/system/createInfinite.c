#include <xinu.h>

void infinite(void);

pid32 createInfinite(
    pri16 prio            // new process priority
){
    pid32 pid = create(infinite,1024,prio,"infinite",0);
    return pid;
}

void infinite(void){
    while(TRUE);
}