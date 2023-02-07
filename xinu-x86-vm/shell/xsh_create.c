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
     int num, modulo;
     num = args[1];
     modulo = num % 2;

     if (modulo == 0)
     {
        printf("Number is even");
     }
    else printf("Number is odd");
    
    return 1;
}