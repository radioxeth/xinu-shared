#include <xinu.h>
#include <stdio.h>

void producer(int*, sid32), consumer(int*, sid32);
pid32 cpid, ppid;
int BUFFER_SIZE = 15;
int count = 200;
/*-------------------------------------------------------------------
* main - Producer and Consumer processes synchronized with semaphores
*--------------------------------------------------------------------
*/
void main(void)
{
	int buffer[BUFFER_SIZE-1];
	sid32 sem;
	sem = semcreate(0);
	
	cpid = create(consumer, 1024, 40, "cons", 3, buffer, sem);
	ppid = create(producer, 1024, 20, "prod", 3, buffer, sem);
	
	resume(cpid);
	resume(ppid);
	
}


/*-------------------------------------------------------------------------
* prod2 - Increment n 2000 times, waiting for it to be consumed
*---------------------------------------------------------------------------
*/
void producer(int* buffer, sid32 sem)
{
	int32 i, bidx;
	bidx = 0;
	for(i=1; i<=count; i++)
	{
		bidx = (i-1) % BUFFER_SIZE;
		buffer[bidx] = i;
		if(bidx==BUFFER_SIZE-1 || i==count) {
			signal(sem);
		}
	}
	kill(cpid);
}

/*-------------------------------------------------------------------------
* cons2 - Print n 2000 times, waiting for it to be produced
*---------------------------------------------------------------------------
*/
void consumer(int* buffer, sid32 sem)
{
	int32 i, c;
	c = 0;
	while(TRUE) {
		wait(sem);
		for(i=0; i<BUFFER_SIZE; i++){
			if(++c<=count){
				kprintf("buffer[%d]=%d\n", i, buffer[i]);
			}
		}
	}
}