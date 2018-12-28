/*
 * include/sim/sched.h
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

#ifndef _SCHED_H
#define _SCHED_H

void sched_step(struct sim_t **sim, int next_arrival_time, int ignore_arrival_time);

#endif
