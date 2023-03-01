/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	uint32 retval;

	
	// Get user input to determine the order
	printf("Enter your rendezvous choice: \n");
	printf("1 ~ Alice speaks first, Bob speaks last. \n");
	printf("2 ~ Alice speaks first, Alice speaks last.  \n");
	printf("3 ~ Bob speaks first, Alice speaks last.  \n");
	printf("4 ~ Bob speaks first, Bob speaks last.  \n");

	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	recvclr();
	while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}
	while (1);

	return OK;
}