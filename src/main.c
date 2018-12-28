/*
 * src/main.c
 *
 * David Vargas
 * CSCI 4334-01 Operating Systems
 * Professor David Egle
 * University of Texas Rio Grande Valley
 *
 * Programming Project Two
 * Due 11/11/16
 *
 */

/* standard c header files */
#include <stdio.h>
#include <stdlib.h>

/* simulator specific header files */
#include <sim/main.h>
#include <sim/proc.h>
#include <sim/sched.h>

void sim_free(struct sim_t **sim)
{
	/* free sim */
	if ((*sim) != NULL) {
		free((*sim));
	}
}

void sim_init(struct sim_t **sim)
{
	(*sim)->status = 1;
	(*sim)->clock = 0;

	(*sim)->start = 0;
	(*sim)->end = 0;

	(*sim)->timeslice = 0;
	(*sim)->overhead = 0;

	(*sim)->avg_wait_time = 0;
	(*sim)->avg_turn_around_time = 0;
	(*sim)->proc_count = 0;

	(*sim)->busy = 0;
	(*sim)->busy_time = 0;

	(*sim)->proc_head = NULL;
	(*sim)->proc_tail = NULL;
}

void sim_main(struct sim_t **sim, int timeslice, int overhead)
{
	sim_init(&(*sim));

	(*sim)->timeslice = timeslice;
	(*sim)->overhead = overhead;

	/* loop through all processes */
	while ((*sim)->status == 1) {
		proc_read(&(*sim));
	}
}

void sim_alloc(struct sim_t **sim)
{
	(*sim) = (struct sim_t *) malloc(sizeof(struct sim_t));

	if ((*sim) == NULL) {
		fprintf(stderr, "sim: error: malloc() failed\n");
		abort();
	}
}

int main()
{
	struct sim_t *sim;

	int overhead;

	sim = NULL;

	sim_alloc(&(sim));

	/* determine the average wait time and average turn around time */

	/* wait time: the time proc spends in the ready state before */
	/*            its first transition to the running state */

	/* turnaround time: the amount of time between the moment proc */
	/*                  first enters the ready state and the moment */
	/*                  the process exits the running state for the */
	/*                  last time */

	/* overhead: 0 5 10 15 20 25 */
	/* timeslice: 50 100 250 500 */
	for (overhead = 0; overhead < 30; overhead += 5) {
		sim_main(&(sim), 50, overhead);
		sim_main(&(sim), 100, overhead);
		sim_main(&(sim), 250, overhead);
		sim_main(&(sim), 500, overhead);
	}

	sim_free(&(sim));

	return 0;
}
