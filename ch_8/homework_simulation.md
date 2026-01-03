## Homework (Simulation)
This program, `mlfq.py`, allows you to see how the MLFQ scheduler
presented in this chapter behaves. See the README for details.

Questions

>1. Run a few randomly-generated problems with just two jobs and
>two queues; compute the MLFQ execution trace for each. Make
>your life easier by limiting the length of each job and turning off
>I/Os.

Job 0 - 2 ms runTime  
Job 1 - 7 ms runTime  
Both queue quantum length - 10 ms  
Start in same priority, round robin. Since both run time are less than the quantum length, they will run in sequence.  

--  
Job 0 - 9 ms runTime  
Job 1 - 1 ms runTime  
Both queue quantum length - 10 ms  
Both will run in sequence until finished.


>2. How would you run the scheduler to reproduce each of the examples
>in the chapter?

For figure 8.6:  
3 queues  
2 jobs  
Higher priority queue has a shorter quantum length, and increases as the priority decreases.  
The job length is sufficient enough that it takes each job down to the lowest priority.

>3. How would you configure the scheduler parameters to behave just
>like a round-robin scheduler?

Allow only one queue, as every job would have the same priority and therefore run in round-robin.  

>4. Craft a workload with two jobs and scheduler parameters so that
>one job takes advantage of the older Rules 4a and 4b (turned on
>with the -S flag) to game the scheduler and obtain 99% of the CPU
>over a particular time interval.

The IO time should be zero, and the non gaming job should never issue an IO. This means that the gaming job
will issue an IO and return from it in the same time step, allowing it to continuously run and gaming the scheduler.

>5. Given a system with a quantum length of 10 ms in its highest queue,
>how often would you have to boost jobs back to the highest priority
>level (with the -B flag) in order to guarantee that a single long-
>running (and potentially-starving) job gets at least 5% of the CPU?

Fraction of CPU time a job gets over an interval would be 10 / T. That share must be
greater than or equal to 0.05 (5%). 10 / 0.05 = 200 ms. The boost interval should be
less than or equal to 200 ms.

>6. One question that arises in scheduling is which end of a queue to
>add a job that just finished I/O; the -I flag changes this behavior
>for this scheduling simulator. Play around with some workloads
>and see if you can see the effect of this flag.

With this flag, jobs that finish an IO are moved to the front of the current queue
they were in. This could lead to gaming by issuing many short IOs so that it stays in the front
of the queue. Without it, those jobs are moved to the back of the queue, allowing for the CPU
bound jobs to run.
