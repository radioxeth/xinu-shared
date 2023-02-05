/*xsh_create.c - xshcreate*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_create - shell command to create a new process with a specific priority
--------------------------------------------------------------------------
*/

shellcmd xsh_create(int nargs, char *args[]){
    pid32	pid;			/* ID of the new process	   */
    pri16 priority;           /* priority of the new process */
    char	ch;			    /* next character of argument	*/
	char	*chptr;			/* walks along argument string	*/
    if (nargs>2){
        kprintf("\nCreate command takes [1] argument, the priority of the new process.\n");
        return 0;
    }
    if(nargs==1){
        priority = 20;
    }
    if(nargs==2){

        chptr = args[1];
        ch = *chptr++;
        priority = 0;
        while(ch != NULLCH) {
            if ( (ch < '0') || (ch > '9') ) {
                kprintf(stderr, "\n%s: non-digit in priotrity\n",
                    args[0]);
                return 1;
            }
            priority = 10*priority + (ch - '0');
            ch = *chptr++;
        }
        
    }
    kprintf("\nCreating process with priority %d\n", priority);
    pid = createInfinite(priority);
    kprintf("\npid: %d\n",pid);
    resume(pid);
    return 1;
}