# xv6

This repository contains a series of assignments based on the xv6 operating system, designed to explore and implement fundamental operating system concepts. Each assignment builds upon the previous, adding complexity and depth to the understanding of OS internals.
Assignment 1: Kernel Threads and Synchronization

## Kernel-level threads and Synchronization
### Objective:
Implement kernel-level threads and synchronization mechanisms to manage concurrent execution within the kernel.

### Key Features:
Developed a kernel thread library to support multiple threads within the kernel.
Implemented POSIX-like system calls:
```
thread_create(): Creates a new kernel thread.
thread_join(): Waits for a specified thread to finish execution.
thread_exit(): Terminates the calling thread.
```

### Introduced synchronization primitives:
Spinlocks: For basic mutual exclusion.
Mutexes: For more flexible synchronization requirements.

### Implementation Highlights:
Modified the kernel's process management to handle multiple threads.
Ensured thread safety and proper synchronization to prevent race conditions.