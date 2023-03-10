/* xsh_sndmsg.c - xsh_sndmsg */

#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_sndmsg - send a message to a pid
 *------------------------------------------------------------------------
 */
shellcmd xsh_sndmsg(int nargs, char *args[])
{
    pid32 pid;
    umsg32 msg;
    int32 i,n;
    /* Insure no arguments were passed */

    if (nargs < 3 || nargs > 4) {
        fprintf(stderr,"use is sndmsg [pid] [msg]\n");
        return 1;
    }else if(nargs = 4){
        pid=atoi(args[1]);
        msg=atoi(args[2]);
        n = atoi(args[3]);
    }else{
        pid=atoi(args[1]);
        msg=atoi(args[2]);
        n = 1;
    }
    
    
    for(i=0;i<n;++i){
        kprintf("sending PID(%4d) msg(%4d)", pid, msg);
        if(sendk(pid, msg)==OK){
            kprintf("OK\n");
        }else{
            kprintf("SYSERR\n");
        }
        msg+=5;
    }
    return 0;
}
