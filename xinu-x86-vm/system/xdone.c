/* xdone.c - xdone */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  xdone  -  Print system completion message as last thread exits
 *------------------------------------------------------------------------
 */
void	xdone(void)
{
	kprintf("\r\n\r\nAll user processes have completed.\r\n\r\n");
	halt();				/* halt the processor		*/
}
