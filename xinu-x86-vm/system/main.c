/*  main.c  - main */

// pre-processor directives
#include <xinu.h>
#include <stdio.h>

// global variables
int32 max_msg = 5;

// global processes
pid32 sender;
pid32 receiver;

// function definitions
void sendyo();
void receivek();

void main(void)
{
	// declare variables
	printf("In main \n");

	//create reciever process, start sender process, then start receiver process	
	sender = create(sendyo, 1024, 50, "sender", 1);  
	receiver = create(receivek, 1024, 50, "receiver",1);
	resume(sender);
	resume(receiver);
}

void sendyo() 
{
	// declare variables
	umsg32 messages[6] = {1,2,3,4,5,6};
	printf("In sendk \n");
	sendk(receiver,messages,6);
}

void receivek() 
{
	printf("In recievek \n");	
	receive();
}