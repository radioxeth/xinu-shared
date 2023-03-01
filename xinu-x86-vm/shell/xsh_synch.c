// Additional libraries
#include <xinu.h>
#include <stdio.h>
#include <string.h>

/* Declare processes, functions, and semaphores globally */
void alice(void);
void bob(void);
sid32 alicesem;
sid32 bobsem;
sid32 sem1;
sid32 sem2;

/*------------------------------------------------------------------------
 * xsh_synch - shell command to run synchronization problem
 *------------------------------------------------------------------------
 */
shellcmd xsh_synch(int nargs, char *args[])
{
	// declare local variables
	int usernum = 0;
	uint32 retval;

	// Get user input
	usernum = atoi(args[1]);
	
	// User input determines the semaphore initialization scheme
	if (usernum == 1)
	{
		alicesem = semcreate(1);
		bobsem = semcreate(0);
		sem1 = semcreate(1);
		sem2 = semcreate(0);		
	}
	else if (usernum == 2)
	{
		alicesem = semcreate(1);
		bobsem = semcreate(0);
		sem1 = semcreate(0);
		sem2 = semcreate(1);	
	}	
	else if (usernum == 3)
	{
		alicesem = semcreate(0);
		bobsem = semcreate(1);
		sem1 = semcreate(0);
		sem2 = semcreate(1);
	}	
	else
	{
		alicesem = semcreate(0);
		bobsem = semcreate(1);
		sem1 = semcreate(1);
		sem2 = semcreate(0);
	}

	// Begin the two processes, Alice begins first
	resume( create(alice, 1024, 20, "alice", 2) );
	resume( create(bob, 1024, 20, "bob", 2) );

	return OK;
}

// Alice has two messages
void alice()
{
	wait(alicesem);
	kprintf("My first statement appears before Bob’s second statement.\n");
	signal(bobsem);		
	wait(sem1);
	kprintf("This is Alice’s second statement.\n");
	signal(sem2);	
}

// Bob has 2 messages
void bob()
{
	wait(bobsem);	
	kprintf("My first statement appears before Alice’s second statement.\n");
	signal(alicesem);
	wait(sem2);
	kprintf("This is Bob’s second statement.\n");
	signal(sem1);
}