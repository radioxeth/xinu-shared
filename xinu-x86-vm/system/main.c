/* main.c - main*/
#include <xinu.h>
#include <stdio.h>

void sndA(void), sndB(void);
void waiter(sid32, sid32), signaler(sid32, sid32);

int n = 2000;
int waitcount = 21;
int increment = 5;

/* 
main - create and run processes, print the queuetab
 */


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
	sid32 semw,sems;
	semw = semcreate(0);
	sems = semcreate(waitcount);
	resume(create(waiter, 1024, 20, "waiter", 2, semw, sems));
	resume(create(signaler, 1024, 20, "signaler", 2, semw, sems));
	
};


/*
signaler - loops and increments the for counter by the increment amount, signals the increment amount
*/
void signaler(
	sid32    semw,
	sid32    sems
){
	int i;
	int inc = waitcount;
	for(i=1;i<=n;i+=inc){
		wait(semw);
		printf("signal\n",i);
		signaln(sems, increment);
		if(i == waitcount+1){
			inc = increment;
		}
	}
}

/*
waiter - loops and waits the semaphore
*/
void waiter(
	sid32    semw,
	sid32    sems
){
	int i;
	int signalcount = waitcount;
	for(i=1;i<=n;i++){
		wait(sems);
		printf("%d ",i);
		if(i == signalcount || i==n){
			signalcount += increment;
			signal(semw);
		}
	}
}

// /*
// signaler - loops and increments the for counter by the increment amount, signals the increment amount
// */
// void signaler(
// 	sid32    sem
// ){
// 	int i;
// 	int inc = waitcount;
// 	for(i=1;i<=n;i+=inc){
// 		printf("signal\n",i);
// 		signaln(sem, increment);
// 		if(i==waitcount+1){
// 			inc = increment;
// 		}
// 	}
// }

// /*
// waiter - loops and waits the semaphore
// */
// void waiter(
// 	sid32    sem
// ){
// 	int i;
// 	for(i=1;i<=n;i++){
// 		printf("%d ",i);
// 		wait(sem);
// 	}
// }


/*
sndA - prints A and then continuously loops
*/
void sndA(void){
	printf("A\n");
	while(1){
		
	}
};

/*
sndB - prints B and then continuously loops
*/
void sndB(void){
	printf("B\n");
	while(1){
		
	}
};
