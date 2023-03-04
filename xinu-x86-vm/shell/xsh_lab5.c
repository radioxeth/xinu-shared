/* xsh_lab5.c - xsh_scheduler, xsh_process */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32 g_xinuSchedulerType; /* Global variable holding the scheduler type value	*/

/*------------------------------------------------------------------------
 * xsh_exit  -  shell command returns the exit code causing shell exit
 *------------------------------------------------------------------------
 */

shellcmd xsh_scheduler(int nargs, char* args[])
{
	int32 i;

	/* Check for valid number of arguments */

	if (nargs > 2)
	{
		fprintf(stderr, "%s: Too many arguments.\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information.\n", args[0]);
		return SHELL_ERROR;
	}

	/* For argument '--help' */

	if (nargs == 2)
	{
		if (strncmp(args[1], "--help", 7) == 0)
		{
			printf("Use: %s #\n\n", args[0]);
			printf("Description:\n");
			printf("\tStarts # of process\n");
			printf("Options:\n");
			printf("\t#     \t This is the scheduler type value.\n");
			printf("\t      \t\t 1 = RRB.\n");
			printf("\t      \t\t 2 = FCFS.\n");
			printf("\t--help\t display this help and exit.\n");
			return SHELL_OK;
		}

		i = atoi(args[1]);
		if (i == SCHED_RRP)
		{
			kprintf("Scheduler type:  Round Robin Priority\n");
			g_xinuSchedulerType = SCHED_RRP;
			return SHELL_OK;
		}
		if (i == SCHED_FCFS)
		{
			kprintf("Scheduler type:  First Come First Serve\n");
			g_xinuSchedulerType = SCHED_FCFS;
			return SHELL_OK;
		}

		fprintf(stderr, "%s: Pick between 1 or 2, Not Hard.\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information.\n", args[0]);
		return SHELL_ERROR;
	}

	fprintf(stderr, "%s: Please 1 or 2.\n", args[0]);
	fprintf(stderr, "Try '%s --help' for more information.\n", args[0]);
	return SHELL_ERROR;
}

shellcmd xsh_process(int nargs, char* args[])
{
	int32 i;
	int16 numberOfProcesses = 3;

	/* Check for valid number of arguments */

	if (nargs > 2)
	{
		fprintf(stderr, "%s: Too many arguments.\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information.\n", args[0]);
		return SHELL_ERROR;
	}

	/* For argument '--help' */

	if (nargs == 2)
	{
		if (strncmp(args[1], "--help", 7) == 0)
		{
			printf("Use: %s [#]\n\n", args[0]);
			printf("Description:\n");
			printf("\tStarts # of process for lab5.\n");
			printf("Options:\n");
			printf("\t[#]   \t This is the number of processes to start.  3 is default value.\n");
			printf("\t--help\t display this help and exit.\n");
			return SHELL_OK;
		}

		i = atoi(args[1]);
		if (i >= 0 && i < 20)

		{
			numberOfProcesses = i;
		}
	}

	pid32 processID;
	pri16 priorityVal = 5;
	char processName[16];

	for (i = 0; i < numberOfProcesses; ++i)
	{
		sprintf(processName, "Process %d", i + 1);
		processID = create(lab5_process, 512, priorityVal, processName, 1, priorityVal);
		resume(processID);
		priorityVal += 5;
	}
	return SHELL_OK;
}