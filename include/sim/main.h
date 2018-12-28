/*
 * include/sim/main.h
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

#ifndef _MAIN_H
#define _MAIN_H

/*
 * average waiting time -- the time p spends in the ready state before
 * 	its first transition to the running state
 *
 */

/*
 * average turnaround time -- the amount of time between the moment p
 * 	first enters the ready state and the moment the process exits
 * 	the running state for the last time.
 *
 */

struct sim_t {
	int status;			/* simulator runtime status */
	int clock;			/* simulator clock */

	int start;			/* timeslice start time */
	int end;			/* timeslice end time */

	int timeslice;			/* timeslice (milliseconds) */
	int overhead;			/* dispatcher overhead (milliseconds) */

	float avg_wait_time;		/* average wait time */
	float avg_turn_around_time;	/* average turn around time */
	int proc_count;			/* process count */

	float busy;			/* busy time (percentage) */
	int busy_time;			/* busy time */

	struct proc_t *proc_head;	/* process table head */
	struct proc_t *proc_tail;	/* process table tail */
};

#endif
