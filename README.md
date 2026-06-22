# UNIX Systems Programming
A collection of C++ programming projects in UNIX environment.

## Projects Included

### 1. [IPC & Dynamic Pipes](./ipc-pipes)
Implementation of dynamic pipelines using multi-process IPC (`fork`, `execvp`, `pipe`, `dup2`). Demonstrates how to connect the standard output of one process to the standard input of another.

* **Key Files:** `DynPipe.cpp`, `TwoPipesTwoChildren.cpp`, `TwoPipesThreeChildren.cpp`
* **How to Run:**
    ```bash
    g++ DynPipe.cpp -o dynpipe
    ./dynpipe "ls -ltr" "grep 3377" "wc -l"
    ```

### 2. [Pthread Matrix Multiplication](./pthread-matrix)
Parallel matrix multiplication using POSIX threads. Demonstrates concurrency, thread creation/joining, and performance optimization.

* **Key File:** `matrix_product.cpp`
* **How to Run:**
    ```bash
    g++ -pthread matrix_product.cpp -o matrix_product
    ./matrix_product
    ```
    *(Note: Ensure `matrixA.txt` and `matrixB.txt` are in the directory.)*

## Tech Stack
* C / C++
* Unix/Linux API
* POSIX Threads
