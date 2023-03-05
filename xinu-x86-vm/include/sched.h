/* sched.h */

/* Constants and variables related to deferred rescheduling */

#define	DEFER_START	1	/* start deferred rescehduling		*/
#define	DEFER_STOP	2	/* stop  deferred rescehduling		*/

/* Structure that collects items related to deferred rescheduling	*/

struct	defer	{
	int32	ndefers;	/* number of outstanding defers 	*/
	bool8	attempt;	/* was resched called during the	*/
				/*   deferral period?			*/
};

extern	struct	defer	Defer;

/* Schedule types */
#define PRIORITY_BASED 0
#define FIFO_BASED 1

extern int32 gschedtype; /* Global variable holding the scheduler type value	*/