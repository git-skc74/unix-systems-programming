# UNIX Systems Programming
A collection of C++ programming projects in UNIX environment.  

This repository includes a `Makefile` for each project.

## Projects Included

### 1. [IPC & Dynamic Pipes](./ipc-pipes)
Implementation of dynamic pipelines using multi-process IPC (`fork`, `execvp`, `pipe`, `dup2`). Demonstrates how to connect the standard output of one process to the standard input of another.

#### Run example
    ./dynpipe "ls -ltr" "grep 3377" "wc -l"

### 2. [Pthread Matrix Multiplication](./pthread-matrix)
Parallel matrix multiplication using POSIX threads. Demonstrates concurrency, thread creation/joining, and performance optimization.

#### Run
    ./matrix_product  
 
*(Note: Ensure `matrixA.txt` and `matrixB.txt` are in the directory.)*

## Tech Stack
* C / C++
* Unix/Linux API
* POSIX Threads
