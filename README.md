# Multi-Process IPC Communication System in C

**A Linux-Based Implementation and Comparative Study of Five Inter-Process Communication Mechanisms**

---

## 1. Project Overview

The **Multi-Process IPC Communication System in C** is a Linux-based application developed to demonstrate and compare five major Inter-Process Communication (IPC) mechanisms. The project focuses on enabling two independent communication endpoints, User A and User B, to exchange messages bidirectionally using different IPC techniques.

The system covers Anonymous Pipes, Named Pipes (FIFOs), System V Message Queues, Shared Memory with Semaphore-Based Synchronization, and TCP Socket Communication.

Each mechanism will be implemented as an independent module and eventually integrated into a unified menu-driven application. The project also aims to evaluate their performance through latency and throughput measurements using the `clock_gettime(CLOCK_MONOTONIC)` function.

## 2. Objectives

- Understand the fundamental concepts and working principles of IPC in Linux.
- Implement five different IPC mechanisms using C and POSIX/Linux system interfaces.
- Establish bidirectional communication between User A and User B.
- Understand process creation, synchronization, and resource management.
- Develop a menu-driven application integrating all five IPC techniques.
- Evaluate communication performance using latency and throughput measurements.
- Generate benchmark reports in CSV format.
- Perform unit testing and integration testing.

## 3. Technologies and Development Environment

| Component | Technology |
|---|---|
| Programming Language | C |
| Operating System | Ubuntu Linux |
| Compiler | GCC |
| Development Interface | Linux Terminal |
| Text Editor | Nano / Vim |
| System Interfaces | POSIX and Linux System Calls |
| Benchmarking | `clock_gettime()` |
| Data Export | CSV |

**Note:** The project is designed to work with standard Linux development tools and does not require additional third-party libraries.

## 4. IPC Mechanisms Covered

The project implements the following five communication techniques:

### 4.1 Anonymous Pipes
A unidirectional communication mechanism that allows related processes, typically created using `fork()`, to exchange data through a kernel-managed buffer. Two pipes are used to achieve bidirectional communication.

### 4.2 Named Pipes (FIFOs)
A communication mechanism that uses a special FIFO file in the filesystem. It allows processes to communicate without requiring a direct parent-child relationship.

### 4.3 System V Message Queues
A message-oriented IPC mechanism that enables processes to exchange structured messages through kernel-managed message queues.

### 4.4 Shared Memory with Semaphores
A high-speed IPC mechanism in which multiple processes access a common memory region. Semaphores are used to synchronize access and prevent race conditions.

### 4.5 TCP Socket Communication
A connection-oriented communication mechanism that enables two processes to exchange data through a TCP connection using socket programming interfaces.

## 5. Current Implementation: Anonymous Pipe Communication

The initial implementation focuses on **Anonymous Pipes** using two communicating processes.

The program creates a parent process representing User A and a child process representing User B through the `fork()` system call.

Two anonymous pipes are established:

- Pipe A-to-B: Transfers messages from User A to User B.
- Pipe B-to-A: Transfers responses from User B to User A.

The implementation supports:

- Bidirectional text communication.
- Parent-child process communication.
- Continuous message exchange.
- Message termination using the `quit` command.
- Complete read and write operations using custom helper functions.
- Handling of interrupted system calls using `errno` and `EINTR`.
- Proper closure of unused file descriptors.
- Child process termination handling using `waitpid()`.

### Important Functions Used

| Function | Purpose |
|---|---|
| `pipe()` | Creates an anonymous pipe. |
| `fork()` | Creates a child process. |
| `read()` | Reads data from a pipe. |
| `write()` | Writes data into a pipe. |
| `close()` | Closes an unused or completed file descriptor. |
| `waitpid()` | Waits for the child process to terminate. |
| `fgets()` | Reads user input from the terminal. |
| `write_full()` | Ensures the requested number of bytes is written. |
| `read_full()` | Reads the requested number of bytes unless EOF or an error occurs. |

## 6. Project Development Status

| Module / Component | Status |
|---|---|
| Project planning and directory structure | Defined |
| Anonymous Pipe source code | Drafted |
| Anonymous Pipe compilation and execution | Pending verification |
| Named Pipe (FIFO) | Pending |
| System V Message Queue | Pending |
| Shared Memory with Semaphores | Pending |
| TCP Socket Communication | Pending |
| Menu-driven integration | Pending |
| Makefile | Pending |
| Benchmarking system | Pending |
| CSV result generation | Pending |
| Unit and integration testing | Pending |
| Architecture diagrams and flowcharts | Pending |
| Final project documentation | In progress |

## 7. Planned Project Structure

The intended directory organization is:

```text
Multi-Process-IPC/
│
├── src/
│   ├── main.c
│   ├── anonymous_pipe.c
│   ├── named_pipe.c
│   ├── message_queue.c
│   ├── shared_memory.c
│   └── tcp_socket.c
│
├── include/
│   └── ipc.h
│
├── benchmark/
│   └── benchmark.c
│
├── tests/
│   └── test_cases.md
│
├── results/
│   └── benchmark_results.csv
│
├── docs/
│   ├── architecture.md
│   └── flowcharts.md
│
├── Makefile
└── README.md
```

*This represents the planned project structure. Additional files may be introduced during integration.*

## 8. Benchmarking and Performance Evaluation

After implementing all five IPC mechanisms, a common benchmarking procedure will be developed to evaluate their communication performance.

The following parameters will be considered:

- **Latency:** Time required to complete a defined message exchange.
- **Throughput:** Amount of data successfully transferred per unit of time.
- **Average Latency:** Mean communication time across repeated test iterations.

The `clock_gettime(CLOCK_MONOTONIC)` function will be used to obtain reliable elapsed-time measurements.

Benchmarking will be performed using consistent message sizes and repeated communication trials wherever practical.

The collected measurements will be exported into CSV files for further analysis and comparison.

**No benchmark results or performance rankings are claimed at the current stage.**

## 9. Testing Strategy

The project will undergo two major categories of testing:

**Unit Testing**
- Verify the individual operation of each IPC module.
- Test message transmission and reception.
- Check process creation and termination.
- Validate synchronization and error-handling mechanisms.
- Verify proper cleanup of IPC resources.

**Integration Testing**
- Verify the menu-driven application.
- Test communication through all five IPC mechanisms.
- Check repeated message exchanges.
- Test termination and resource cleanup.
- Validate the benchmarking and CSV export functionality.

## 10. Expected Outcome

The completed application is expected to provide a practical demonstration of five different IPC mechanisms through a common communication interface.

It will help users understand the differences between process-based, message-based, shared-memory, and network-based communication models.

The benchmarking component will provide experimental observations about latency and throughput under the tested laboratory environment.

The final submission is expected to include complete C source files, a Makefile, test cases, benchmark datasets, architecture documentation, flowcharts, and a detailed project report.

## 11. Limitations and Future Scope

The initial implementation is designed for a Linux environment and uses standard Linux/POSIX interfaces.

The anonymous-pipe source code has been drafted, but compilation and execution on the college laboratory computer are yet to be verified. The remaining modules and integration work are planned development activities.

Future improvements may include:

- Testing with different message sizes.
- Evaluating the effects of increased communication frequency.
- Measuring synchronization overhead.
- Supporting multiple communicating clients.
- Extending performance analysis across different Linux systems.

---

**Project Title:** Multi-Process IPC Communication System in C  
**Platform:** Ubuntu Linux  
**Language:** C  
**Compiler:** GCC  
**Project Type:** Operating Systems / Systems Programming  
**Primary Focus:** Inter-Process Communication and Performance Analysis
