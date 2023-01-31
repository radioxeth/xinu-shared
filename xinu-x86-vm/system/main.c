/* main.c - main*/
#include <xinu.h>
#include <stdio.h>

void sndA(void), sndB(void);
void waiter(sid32), signaler(sid32);

int n = 200;
int waitcount = 20;
int increment = 5;

/* 
main - create and run processes, print the queuetab
 */


// sid32 sem1, sem2;


void main(void)
{
	// Part 1
	// resume(create(sndA,1024,20,"snda",0));
	// resume(create(sndB,1024,20,"sndb",0));
	// resume(create(sndA,1024,20,"snda",0));
	// resume(create(sndB,1024,20,"sndb",0));
	// resume(create(sndA,1024,20,"snda",0));
	// resume(create(sndB,1024,20,"sndb",0));
	// resume(create(printqueuetab,1024,20,"print queue",0));

	// Part 2
	sid32 sem;
	sem = semcreate(waitcount);
	
	resume(create(waiter, 1024, 40, "waiter", 1, sem));
	resume(create(signaler, 1024, 20, "signaler", 1, sem));
	
};

void signaler(
	sid32    sem
){
	int i;
	int inc=waitcount;
	for(i=1;i<=n;i+=inc){
		printf("signal\n",i);
		signaln(sem, increment);
		if(i==waitcount+1){
			inc = increment;
		}
	}
}

void waiter(
	sid32    sem
){
	int i;
	for(i=1;i<=n;i++){
		printf("%d ",i);
		wait(sem);
	}
}






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
