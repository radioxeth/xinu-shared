/* xsh_recmsg.c - xsh_recmsg */

#include <xinu.h>
#include <stdio.h>

void receiver(void);

/*------------------------------------------------------------------------
 * xsh_recmsg - receive and print a message
 *------------------------------------------------------------------------
 */
shellcmd xsh_recmsg(int nargs, char *args[])
{

    /* Insure no arguments were passed */

    if (nargs > 1) {
        fprintf(stderr,"use is recmsg\n");
        return 1;
    }
    resume(create(receiver, 1024, 15, "receiver", 0));
    return 0;
}

void receiver(void)
{
    umsg32 msg;
    pid32 pid = getpid();
    kprintf("PID(%d) is receiving\n",pid);
    while(TRUE){
        msg = receivek();
        kprintf("PID(%d) received msg(%d)\n", pid, msg);
    }
}
