/*
 * include/sim/proc.h
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

#ifndef _PROC_H
#define _PROC_H

struct proc_t {
	int arrival_time;	/* arrival time */
	float service_time;	/* service time */

	int proc_state;		/* 0 = hasn't run, 1 = has run */

	int wait_end;
	int running_end;

	int wait_time;		/* wait_end - arrival_time */
	int turn_around_time;	/* running_end - wait_end */

	struct proc_t *next;
};

void proc_read(struct sim_t **sim);
void proc_pop_front(struct sim_t **sim);
void proc_context_switch(struct sim_t **sim);
void proc_print_table(struct sim_t **sim);

#endif
