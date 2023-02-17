/*  main.c  - main */

// Additional libraries
#include <xinu.h>
#include <stdio.h>

/* Declare processes, functions, and semaphores globally */
void alice(sid32,sid32);
void bob(sid32,sid32);


// This code demonstrates a rendezvous between Alice and Bob 
// aka Alice has to wait for Bob and vice versa 
// each process must wait for the other depending who speaks first
int main()
{
	// declare local variables
	int usernum = 3;
	sid32 alicesem;
	sid32 bobsem;	
	uint32 retval;
	
	// Get user input to determine the order
	printf("Enter your rendezvous choice: \n");
	printf("1 ~ Alice speaks first, Bob speaks last. \n");
	printf("2 ~ Alice speaks first, Alice speaks last.  \n");
	printf("3 ~ Bob speaks first, Alice speaks last.  \n");
	printf("4 ~ Bob speaks first, Bob speaks last.  \n");

	// Get the user input using the shell
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	// Wait for shell to exit 
	recvclr();
	//while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process destroying shell\n\n\r");
	//}
	
	// User input determines the semaphore initialization scheme
	if (usernum == 1)
	{
		alicesem = semcreate(1);
		bobsem = semcreate(0);
	}
	else if (usernum == 2)
	{
		alicesem = semcreate(1);
		bobsem = semcreate(0);
	}	
	else if (usernum == 3)
	{
		alicesem = semcreate(0);
		bobsem = semcreate(1);
	}	
	else
	{
		alicesem = semcreate(0);
		bobsem = semcreate(1);
	}

	// Begin the two processes
	resume( create(alice, 1024, 20, "alice", 2, alicesem, bobsem) );
	resume( create(bob, 1024, 20, "bob", 2, alicesem, bobsem) );

	return OK;
}

// Alice has two messages
void alice(sid32 alicesem, sid32 bobsem)
{
	wait(alicesem);
	printf("My first statement appears before Bob’s second statement.\n");
	signal(bobsem);
	wait(alicesem);
	printf("This is Alice’s second statement.\n");
	signal(bobsem);	
}

// Bob has 2 messages
void bob(sid32 alicesem, sid32 bobsem)
{
	wait(bobsem);
	printf("My first statement appears before Alice’s second statement.\n");
	signal(alicesem);
	wait(bobsem);
	printf("This is Bob’s second statement.\n");
	signal(alicesem);	
}