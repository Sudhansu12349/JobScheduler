# Job Scheduler

A C++ simulation of an operating system-inspired **tick-based job scheduler** that models the lifecycle of jobs using a **hybrid, non-preemptive scheduling algorithm**. The scheduler executes on a single thread and advances one clock tick at a time, demonstrating how jobs move through different scheduling states based on arrival time, priority, and execution duration.

## Features

* Tick-based execution simulation
* Hybrid scheduling strategy (Priority + FCFS tie-breaking)
* Non-preemptive scheduling
* Single-threaded scheduler
* Ready, Waiting, Running, and Completed job states
* Configurable execution policies
* Job lifecycle management
* Simulation clock for discrete time progression

## Scheduling Strategy

The scheduler operates on discrete clock ticks.

* Jobs enter the **Waiting** state until their scheduled arrival time.
* Once eligible, they are moved to the **Ready Queue**.
* The scheduler selects the highest-priority ready job for execution.
* If multiple jobs have the same priority, **First Come First Served (FCFS)** is used as the tie-breaker.
* Once a job starts executing, it runs **to completion** without interruption (non-preemptive execution).

## Architecture

### Core Components

* **Job** – Stores job metadata, execution time, priority, arrival time, and current state.
* **Scheduler** – Controls scheduling decisions, queue transitions, and execution.
* **Clock** – Advances the simulation one tick at a time.
* **Execution Policy** – Encapsulates scheduling rules for selecting the next job.

## Data Structures Used

* `priority_queue` for scheduling ready jobs
* `queue` for waiting and completed jobs
* `unordered_map` for fast job lookup by ID
* STL containers and custom comparators

## Project Structure

```
Job Scheduler/
│
├── include/
│   ├── Clock.h
│   ├── Job.h
│   ├── Scheduler.h
│   ├── ExecutionPolicy.h
│   ├── Comparators.h
│   └── JobState.h
│
├── src/
│   ├── main.cpp
│   ├── Job.cpp
│   ├── Scheduler.cpp
│   └── Clock.cpp
│
├── README.md
└── .gitignore
```

## Build

Compile the project using:

```bash
g++ src/*.cpp -Iinclude -o scheduler
```

Run:

```bash
./scheduler
```

## Future Enhancements

* Preemptive scheduling algorithms
* Round Robin scheduling
* Multi-threaded execution
* Persistent job storage
* Scheduling statistics and performance metrics
* Interactive command-line interface improvements

## Concepts Demonstrated

* Object-Oriented Programming (OOP)
* Data Structures using STL
* Priority-based scheduling
* Operating System scheduling concepts
* Event-driven simulation
* Modular software design
