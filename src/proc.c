/*
 * src/proc.c
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

void proc_print_table(struct sim_t **sim)
{
	struct proc_t *itr;

	itr = (*sim)->proc_head;

	while (itr != NULL) {
		printf("node = %i\t%f\n", itr->arrival_time, itr->service_time);
		itr = itr->next;
	}

	printf("\n");
}

void proc_context_switch(struct sim_t **sim)
{
	/* should never happen */
	if ((*sim)->proc_head == NULL) {
		return;
	}

	/* single process context switch */
	if ((*sim)->proc_head->next == NULL) {
		/* ch07a.pptx -- slide 84 */
		/* include overhead for a context switch of the same process */
		(*sim)->clock += (*sim)->overhead;

		/* start timeslice */
		(*sim)->start = (*sim)->clock;
		(*sim)->end = (*sim)->clock + (*sim)->timeslice;
		return;
	}

	/* context switch */
	(*sim)->proc_tail->next = (*sim)->proc_head;
	(*sim)->proc_head = (*sim)->proc_head->next;
	(*sim)->proc_tail = (*sim)->proc_tail->next;
	(*sim)->proc_tail->next = NULL;

	/* include overhead */
	(*sim)->clock += (*sim)->overhead;

	/* start timeslice */
	(*sim)->start = (*sim)->clock;
	(*sim)->end = (*sim)->clock + (*sim)->timeslice;
}

void proc_pop_front(struct sim_t **sim)
{
	struct proc_t *ptr;

	/* should never happen */
	if ((*sim)->proc_head == NULL) {
		return;
	}

	ptr = (*sim)->proc_head;

	/* context switch */
	(*sim)->proc_head = (*sim)->proc_head->next;

	/* include overhead */
	(*sim)->clock += (*sim)->overhead;

	/* single process pop */
	if ((*sim)->proc_head == NULL) {
		(*sim)->proc_tail = NULL;
	}

	/* start timeslice */
	(*sim)->start = (*sim)->clock;
	(*sim)->end = (*sim)->clock + (*sim)->timeslice;

	free(ptr);
}

void proc_push_back(struct sim_t **sim, struct proc_t **proc)
{
	/* empty table? */
	if ((*sim)->proc_tail == NULL) {
		(*sim)->proc_tail = (*proc);
		(*sim)->proc_head = (*proc);

		/* start timeslice */
		(*sim)->start = (*sim)->clock;
		(*sim)->end = (*sim)->clock + (*sim)->timeslice;
	} else {
		(*sim)->proc_tail->next = (*proc);
		(*sim)->proc_tail = (*proc);
	}

	(*proc)->next = NULL;
}

void proc_read(struct sim_t **sim)
{
	FILE *fp;

	struct proc_t *proc;

	int ret;

	fp = fopen("doc/times.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "sim: error: fopen() failed\n");
		abort();
	}

	proc = (struct proc_t *) malloc(sizeof(struct proc_t));
	ret = fscanf(fp, "%i %f", &(proc->arrival_time), &(proc->service_time));

	/* convert seconds to milliseconds */
	proc->arrival_time *= 1000;
	proc->service_time *= 1000;

	/* proc hasn't run */
	proc->proc_state = 0;

	/* increment proc_count */
	(*sim)->proc_count++;

	/* loop through the input file */
	while (ret != EOF) {
		/* step through simulator until next arrival_time */
		sched_step(&(*sim), proc->arrival_time, 0);

		/* insert process into simulator process table */
		proc_push_back(&(*sim), &(proc));

		proc = (struct proc_t *) malloc(sizeof(struct proc_t));
		ret = fscanf(fp, "%i %f", &(proc->arrival_time), &(proc->service_time));

		/* convert seconds to milliseconds */
		proc->arrival_time *= 1000;
		proc->service_time *= 1000;

		/* proc hasn't run */
		proc->proc_state = 0;

		/* increment proc_count */
		(*sim)->proc_count++;
	}

	/* loop through the remaining processes */
	while ((*sim)->proc_head != NULL) {
		/* continue through simulator until the end */
		sched_step(&(*sim), 0, 1);
	}

	/* all processes finished */
	(*sim)->status = 0;

	/* calculate averages */
	(*sim)->avg_wait_time = (*sim)->avg_wait_time / ((float) (*sim)->proc_count);
	(*sim)->avg_turn_around_time = (*sim)->avg_turn_around_time / ((float) (*sim)->proc_count);

	/* calculate busy time (percentage) */
	(*sim)->busy = ((float) (*sim)->busy_time / (float) (*sim)->clock) * 100.00;

	printf("Using overhead: '%i' and timeslice: '%i'\n", (*sim)->overhead, (*sim)->timeslice);
	printf("avg_wait_time: '%f'\n", (*sim)->avg_wait_time);
	printf("avg_turn_around_time: '%f'\n", (*sim)->avg_turn_around_time);
	printf("busy_time: '%i'\n", (*sim)->busy_time);
	printf("clock: '%i'\n", (*sim)->clock);
	printf("busy: '%f'\n\n", (*sim)->busy);

	free(proc);

	fclose(fp);
}
