/* lab5.c - lab5_process */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  lab5_process2 - process prints ID only once and then sleeps for 15 seconds
 *------------------------------------------------------------------------
 */
syscall lab5_process(
    int16 priority /* Priority value for this process */
)
{
    kprintf("priority & pid: [%d,%d]\n", priority, getpid());

    sleep(15);

    int16 i;
    for (i = 0; i < 100; ++i)
        // while (TRUE)
    {
        kprintf("priority & pid: [%d,%d] - %d\n", priority, getpid(), i);
    }

    return OK;
}