/*xsh_bufferprint.c - xshbufferprint*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_bufferprint - shell command to print 1 to n using a buffer
--------------------------------------------------------------------------
*/
void producer(int*, sid32), consumer(int*, sid32);
pid32 cpid, ppid;
int BUFFER_SIZE = 15;
int count;

shellcmd xsh_bufferprint(int nargs, char *args[]){
    if (nargs>2){
        kprintf("Create command takes [1] argument, process to count to\n");
        return 0;
    } else if (nargs==1){
        count = 2000;
    } else if(nargs==2){
        count = atoi(args[1]);
    }
    if(count < BUFFER_SIZE){
        kprintf("please enter a digit priority greater than 0\n");
        return 0;
    }

    int buffer[BUFFER_SIZE-1];
	sid32 sem;
	sem = semcreate(0);
	
	cpid = create(consumer, 1024, 40, "cons", 2, buffer, sem);
	ppid = create(producer, 1024, 20, "prod", 2, buffer, sem);
	
	resume(cpid);
	resume(ppid);
    
    return 1;
}

/*-------------------------------------------------------------------------
* producer - Increment n 2000 times, filling the buffer
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
* consumer - Print the buffer, if there room left in the count
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