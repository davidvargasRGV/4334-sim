#
# Simulator Makefile
#
# David Vargas
# CSCI 4334-01 Operating Systems
# Professor David Egle
# University of Texas Rio Grande Valley
#
# Programming Project Two
# Due 11/11/16
#

CC = gcc
CFLAGS = -Wall -I./include/

RM = rm
RFLAGS = -f

OBJ = ./bin/main.o ./bin/proc.o ./bin/sched.o

all: sim
	@echo "Built Simulator"

sim: main.o proc.o sched.o
	$(CC) $(CFLAGS) $(OBJ) -o ./bin/sim

main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -o ./bin/main.o

proc.o: ./src/proc.c
	$(CC) $(CFLAGS) -c ./src/proc.c -o ./bin/proc.o

sched.o: ./src/sched.c
	$(CC) $(CFLAGS) -c ./src/sched.c -o ./bin/sched.o

clean:
	$(RM) $(RFLAGS) ./bin/*.o
	$(RM) $(RFLAGS) ./bin/sim
