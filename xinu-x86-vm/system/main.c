/* main.c - main*/
#include <xinu.h>

void sndA(void), sndB(void);

/* 
main - create and run two processes
sndA which continuously prints the character A
sndB which continuously prints the character B
 */
void main(void)
{
  resume(create(sndA,1024,40,"sndA",0));
  resume(create(sndB,1024,20,"sndB",0));
};

/*
sndA - continuously prints the character A
*/
void sndA(void){
	while(1){
		putc(CONSOLE,'A');
	}
};

/*
sndB - continuously prints the character B
*/
void sndB(void){
	while(1){
		putc(CONSOLE,'B');
	}
};
