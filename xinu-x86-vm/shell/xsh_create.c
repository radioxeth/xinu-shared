/*xsh_create.c - xshcreate*/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
/*
--------------------------------------------------------------------------
xsh_create - shell command to create a new process with a specific priority
--------------------------------------------------------------------------
*/

shellcmd xsh_create(int nargs, char *args[])
{
     char inp;
     int num, modulo;
     inp = args[1];
     num = (int)(inp);
     modulo = num % 2;

     if (modulo == 0)
     {
        printf("Number is even");
     }
    else printf("Number is odd");
    
    return 1;
}