/*xsh_bufferprint.c - xshbufferprint*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_synch - shell command to run synchronization problem
--------------------------------------------------------------------------
*/
void alice(sid32,sid32), bob(sid32,sid32);
pid32 apid, bpid;
pri16 alicePrio, bobPrio;
int s1,s2;

shellcmd xsh_synch(int nargs, char *args[]){
    if (nargs != 3) {
        kprintf("Create command takes [2] arguments, who speaks first and who speaks second\n");
        return 0;
    } else {
        s1 = atoi(args[1]);
        s2 = atoi(args[2]);
    }
    /*
    0 == alice
    1 == bob
    */
    if (s1 < 0 || s1 > 1){
        kprintf("please enter 0 (for alice) or 1 (for bob) to speak first\n");
        return 0;
    }
    if (s2 < 0 || s2 > 1){
        kprintf("please enter 0 (for alice) or 1 (for bob) to speak second\n");
        return 0;
    }
	sid32 asem,bsem;
    if (s1==0 && s2==0) {
        alicePrio = 20;
        bobPrio   = 20;
        asem = semcreate(1);
        bsem = semcreate(0);
    } 
    else if (s1==1 && s2==1) {
        alicePrio = 20;
        bobPrio   = 20;
        asem = semcreate(0);
        bsem = semcreate(1);
    }

    else if (s1==0 && s2==1) {
        alicePrio = 20;
        bobPrio   = 40;
        asem = semcreate(1);
        bsem = semcreate(0);
    }
    else if (s1==1 && s2==0) {
        alicePrio = 40;
        bobPrio   = 20;
        asem = semcreate(0);
        bsem = semcreate(1);
    }
    else {
        return 0;
    }

    apid = create(alice, 1024, alicePrio, "alice", 2, asem, bsem);
	bpid = create(bob, 1024, bobPrio, "bob", 2, asem, bsem);
	
	resume(apid);
	resume(bpid);
    return 1;
}

/*-------------------------------------------------------------------------
* alice - Print Alice's statements depending on whose turn it is
*---------------------------------------------------------------------------
*/
void alice(sid32 asem, sid32 bsem)
{
    wait(asem);
	printf("A1: My first statement appears before Bob's second statement.\n");
    if (s1==s2) {
        signal(bsem);
        wait(asem);
    }
    else if (s2==1) { // if Bob speaks first in the second set of statements, signal Bob
        signal(bsem);
    }
    printf("A2: This is Alice's second statement.\n");
    signal(bsem);
}

/*-------------------------------------------------------------------------
* bob - Print Bob's statements depending on whose turn it is
*---------------------------------------------------------------------------
*/
void bob(sid32 asem, sid32 bsem)
{
    wait(bsem);
	printf("B1: My first statement appears before Alices's second statement.\n");
    if (s1==s2) {
        signal(asem);
        wait(bsem);
    }
    else if (s2==0) { // if Alice speaks first in the second set of statements, signal Alice
        signal(asem);
    }
    printf("B2: This is Bob's second statement.\n");
    signal(asem);
}
