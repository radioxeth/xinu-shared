/* main.c - main*/
#include <xinu.h>
#include <stdio.h>

void sndA(void), sndB(void);
void printQueue(void);

/* 
main - create and run two processes
sndA which continuously prints the character A
sndB which continuously prints the character B
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

// void printQueueTable(void){
// 	// int i=0;
// 	// while (i<NPROC){
// 	// 	if(isbadpid(i)==0) {
// 	// 		printf("pid=%d|qkey=%d|qprev=%d|qnext=%d\n",i,queuetab[i].qkey,queuetab[i].qprev,queuetab[i].qnext);
// 	// 	}
// 	// 	i++;
// 	// }
	
// 	// printf("-------------------------\n");
// 	// while (i<NQENT){
// 	// 	if(nonempty(i) && firstid(i)!=-1){
// 	// 		printf("pid=%d|qkey=%d|qprev=%d|qnext=%d\n",i,queuetab[i].qkey,queuetab[i].qprev,queuetab[i].qnext);
// 	// 		i++;
// 	// 		printf("pid=%d|qkey=%d|qprev=%d|qnext=%d\n",i,queuetab[i].qkey,queuetab[i].qprev,queuetab[i].qnext);
// 	// 	}
// 	// 	i++;
// 	// }
// };
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
