# 4334-sim

This is the source code for the Round Robin Scheduling Simulator assignment for CSCI 4334 Operating Systems at the University of Texas Rio Grande Valley.

The textbook for the course was **Operating Systems - A Modern Perspective** by Gary Nutt.

## Building

A makefile is provided. Simply execute the following...

```
make
```

The following is the directory structure...

* bin - C object files and Shell binary
* doc - input/output files
* include/sh - C header files
* src - C source files

## Running

To execute the Round Robin Simulator, simply execute the following... 

```
./bin/sim
```

**Note**: *./doc/times.txt* is required.

**Note**: Output is verbose. It is recommended to redirect output to a file.

## Example

To execute the Round Robin Scheduling Simulator, simply execute the following...

```
./bin/sim > ./doc/output.txt
```

**Note**: Line charts of the output have been made in *./doc/charts.xls*.

## Authors

* David Vargas (*david.vargas.rgv [AT] gmail.com*)

## License

All rights reserved.

## Acknowledgments

None
