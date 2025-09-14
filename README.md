# xv6

This repository contains a series of assignments based on the xv6 operating system, designed to explore and implement fundamental operating system concepts. Each assignment builds upon the previous, adding complexity and depth to the understanding of OS internals.

## 1: Kernel-level threads and Synchronization
### Objective:
Implement kernel-level threads and synchronization mechanisms to manage concurrent execution within the kernel.

### Key Features:
- Developed a kernel thread library to support multiple threads within the kernel.
- Implemented POSIX-like system calls:
```
thread_create(): Creates a new kernel thread.
thread_join(): Waits for a specified thread to finish execution.
thread_exit(): Terminates the calling thread.
```

- Introduced synchronization primitives:
- Spinlocks: For basic mutual exclusion.
- Mutexes: For more flexible synchronization requirements.

### Implementation Highlights:
- Modified the kernel's process management to handle multiple threads.
Ensured thread safety and proper synchronization to prevent race conditions.


## 2: Hybrid Scheduler
### Objective: 
Added system calls and modified scheduler to use Shortest Job First (SJF) method along with Round Robin scheduling

### Key Features:
- Introduced new system calls to interact with the scheduler:
```
getNumProc(): Returns the number of processes currently in the system.
getMaxPid(): Returns the maximum process ID assigned.
getProcInfo(pid, &processInfo): Retrieves detailed information about a specific process.
```
- Implemented a hybrid scheduling algorithm that combines aspects of multiple scheduling strategies to improve system performance.

### Implementation Highlights:
- Modified the scheduler to incorporate the new hybrid algorithm.
- Added necessary data structures to support the new system calls and scheduling logic.

## 3: Memory Management

### Objective:
Enhance the memory management subsystem to support advanced features like lazy allocation and paging.

### Key Features:
- Implemented lazy memory allocation to defer the allocation of physical memory until it is actually needed.
- Introduced paging mechanisms to manage virtual memory more efficiently.

### Implementation Highlights:
- Modified the `sbrk()` system call to implement lazy allocation.
- Handled page faults and managed page tables to support virtual memory.

## 4: Quantitative Comparison of Filesystems

### Objective:
Conduct a quantitative comparison between different filesystem implementations to evaluate their performance.

### Key Features:
- Implemented multiple filesystem types to compare their performance characteristics.
- Designed benchmarks to test various filesystem operations under different conditions.

### Implementation Highlights:
- Developed tools to measure filesystem performance metrics.
- Analyzed the results to draw conclusions about the strengths and weaknesses of each filesystem implementation.

