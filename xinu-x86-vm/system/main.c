/*  main.c  - main */

// Additional libraries
#include <xinu.h>
#include <stdio.h>

/* Declare processes, functions, and semaphores globally */
void alice(void);
void bob(void);
sid32 alicesem;
sid32 bobsem;
sid32 sem1;
sid32 sem2;

// This code demonstrates a rendezvous between Alice and Bob 
// aka Alice has to wait for Bob and vice versa 
// each process must wait for the other depending who speaks first
int main()
{
	// declare local variables
	int usernum = 4;
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
	printf("My first statement appears before Bob’s second statement.\n");
	sleep(2);
	signal(bobsem);		
	wait(sem1);
	sleep(2);	
	printf("This is Alice’s second statement.\n");
	sleep(2);	
	signal(sem2);	
}

// Bob has 2 messages
void bob()
{
	wait(bobsem);	
	printf("My first statement appears before Alice’s second statement.\n");
	sleep(2);	
	signal(alicesem);
	wait(sem2);
	sleep(2);
	printf("This is Bob’s second statement.\n");
	sleep(2);
	signal(sem1);
}