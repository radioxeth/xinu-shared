/* ex5.c - main, prod2 cons2 */

#include <xinu.h>
void prod2(sid32, sid32), cons2(sid32, sid32);

sid32 sem;
int32 n = 0; /* Variable n has inital value zero */
int buffer[15]; // global array to act as buffer

/*-------------------------------------------------------------------
* main - Producer and Consumer processes synchronized with semaphores
*--------------------------------------------------------------------
*/ 
void main(void)
{
	// Initiate the semaphore to 14 (size of the buffer -1)
	sem = semcreate(14);

	sid32 produced, consumed;
	consumed = semcreate(0);
	produced = semcreate(14);
	resume( create(cons2, 1024, 20, "cons", 2, consumed, produced) );
	resume( create(prod2, 1024, 20, "prod", 2, consumed, produced) );
}

/*-------------------------------------------------------------------------
* prod2 - add to buffer and signal in loop from 1 to 15
*---------------------------------------------------------------------------
*/
void prod2(sid32 consumed, sid32 produced)
{
	int32 i;
	for(i=1; i<=15; i++)
	{
		wait(consumed);
		buffer[i-1] = i;
		n++;
		signal(produced);
	}
}

/*-------------------------------------------------------------------------
* cons2 - wait for buffer to be full (sem = -1) then print buffer
*---------------------------------------------------------------------------
*/
void cons2(sid32 consumed, sid32 produced)
{
	int32 i;
	for(i=15; i>0; i--)
	{
		wait(produced);
		printf("Buffer space %d = %d \n",i, buffer[i-1]);
		signal(consumed);
	}
}