/*
 * src/sched.c
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

/* simulator specific header files */
#include <sim/main.h>
#include <sim/proc.h>
#include <sim/sched.h>

void sched_step(struct sim_t **sim, int next_arrival_time, int ignore_arrival_time)
{
	/* ignore arrival time OR loop through timeslices until next arrival time */
	while ((ignore_arrival_time) || ((*sim)->clock < next_arrival_time)) {
		/* no processes -- skip forward to next_arrival_time */
		if ((*sim)->proc_head == NULL) {
			if (!(ignore_arrival_time)) {
				(*sim)->clock = next_arrival_time;
			}
			break;
		}

		/* process finished? */
		if ((*sim)->proc_head->service_time <= 0) {
			(*sim)->proc_head->running_end = (*sim)->clock;
			(*sim)->proc_head->turn_around_time = (*sim)->proc_head->running_end - (*sim)->proc_head->wait_end;

			(*sim)->avg_wait_time += (*sim)->proc_head->wait_time;
			(*sim)->avg_turn_around_time += (*sim)->proc_head->turn_around_time;

			proc_pop_front(&(*sim));

			continue;
		}

		/* timeslice finished? */
		if ((*sim)->start == (*sim)->end) {
			proc_context_switch(&(*sim));

			continue;
		}

		/* process hasn't run before? */
		if ((*sim)->proc_head->proc_state == 0) {
			(*sim)->proc_head->wait_end = (*sim)->clock;
			(*sim)->proc_head->wait_time = (*sim)->proc_head->wait_end - (*sim)->proc_head->arrival_time;

			(*sim)->proc_head->proc_state = 1;
		}

		/* increment clock */
		(*sim)->clock += 1;

		/* decrement service_time */
		(*sim)->proc_head->service_time -= 1;

		/* increment timeslice */
		(*sim)->start++;

		/* increment busy time */
		(*sim)->busy_time++;
	}
}
