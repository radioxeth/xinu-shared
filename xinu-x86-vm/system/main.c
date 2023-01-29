/* main.c - main*/
#include <xinu.h>
#include <stdio.h>

void sndA(void), sndB(void);

/* 
main - create and run processes, print the queuetab
 */
void main(void)
{
	resume(create(sndA,1024,20,"snda",0));
	resume(create(sndB,1024,20,"sndb",0));
	resume(create(sndA,1024,20,"snda",0));
	resume(create(sndB,1024,20,"sndb",0));
	resume(create(sndA,1024,20,"snda",0));
	resume(create(sndB,1024,20,"sndb",0));
	resume(create(printqueuetab,1024,20,"print queue",0));
};

/*
sndA - continuously prints the character A
*/
void sndA(void){
	printf("A\n");
	while(1){
		
	}
};

/*
sndB - continuously prints the character B
*/
void sndB(void){
	printf("B\n");
	while(1){
		
	}
};
