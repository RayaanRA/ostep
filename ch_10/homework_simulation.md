## Homework (Simulation)
In this homework, we’ll use multi.py to simulate a multi-processor
CPU scheduler, and learn about some of its details. Read the related
README for more information about the simulator and its options.

Questions

>1. To start things off, let’s learn how to use the simulator to study how to build an effective multi-processor scheduler. The first simulation will run just one job, which has a runtime of 30, and a working-set size of 200. Run this job (called job ’a’ here) on one simulated CPU as follows: `./multi.py -n 1 -L a:30:200`. How long will it take to complete? Turn on the -c flag to see a final answer, and the -t flag to see a tick-by-tick trace of the job and how it is scheduled.

Finished time 30.

>2. Now increase the cache size so as to make the job’s working set
(size=200) fit into the cache (which, by default, is size=100); for
example, run `./multi.py -n 1 -L a:30:200 -M 300`. Can
you predict how fast the job will run once it fits in cache? (hint:
remember the key parameter of the warm rate, which is set by the
-r flag) Check your answer by running with the solve flag (-c) enabled.

If warmup rate is 10 units, and warmup increases speed by 2x, then it should finish in 20 time units.

>3. One cool thing about multi.py is that you can see more detail
about what is going on with different tracing flags. Run the same
simulation as above, but this time with time left tracing enabled
(-T). This flag shows both the job that was scheduled on a CPU
at each time step, as well as how much run-time that job has left
after each tick has run. What do you notice about how that second
column decreases?

It first decreases by one, then by two after warming up to show the efficiency when the CPU has the program's data in cache.

>4. Now add one more bit of tracing, to show the status of each CPU
cache for each job, with the -C flag. For each job, each cache will
either show a blank space (if the cache is cold for that job) or a ’w’ (if the cache is warm for that job). At what point does the cache become warm for job ’a’ in this simple example? What happens as you change the warmup time parameter (-w) to lower or higher
values than the default?

It becomes warm on the tenth time unit. Changing to a lower warmup time decreases total runtime, while a higher warmup makes it take longer.

>5. At this point, you should have a good idea of how the simulator works for a single job running on a single CPU. But hey, isn’t
this a multi-processor CPU scheduling chapter? Oh yeah! So let’s
start working with multiple jobs. Specifically, let’s run the following three jobs on a two-CPU system (i.e., type `./multi.py -n
2 -L a:100:100,b:100:50,c:100:50`) Can you predict how
long this will take, given a round-robin centralized scheduler? Use
-c to see if you were right, and then dive down into details with -t
to see a step-by-step and then -C to see whether caches got warmed
effectively for these jobs. What do you notice?

Each process must run for 10 quantums. In each time slice, both CPUs only run one single job. For example, in the first quantum, CPU 0 runs `a` and CPU 1 runs `b`. Then CPU 0 runs `c` and loops until every process finishes. Finished time 150.

>6. Now we’ll apply some explicit controls to study cache affinity, as described in the chapter. To do this, you’ll need the -A flag. This flag can be used to limit which CPUs the scheduler can place a particular job upon. In this case, let’s use it to place jobs ’b’ and ’c’ on CPU 1, while restricting ’a’ to CPU 0. This magic is accomplished by typing this `./multi.py -n 2 -L a:100:100,b:100:50,
c:100:50 -A a:0,b:1,c:1`; don’t forget to turn on various tracing options to see what is really happening! Can you predict how
fast this version will run? Why does it do better? Will other combinations of ’a’, ’b’, and ’c’ onto the two processors run faster or slower?

It runs better as process `a`'s working set size always remains on the CPU's cache since it fills the CPU cache exactly and is restricted to run on CPU 0, unlike before, and on CPU 1 `b` and `c` run in round robin. However, CPU 0 becomes idle while the other two processes run on CPU 1. If `a` shares with another process, it'd take longer because the CPU cannot store both `a`'s and another process's cache.

>7. One interesting aspect of caching multiprocessors is the opportunity for better-than-expected speed up of jobs when using multiple CPUs (and their caches) as compared to running jobs on a single processor. Specifically, when you run on N CPUs, sometimes
you can speed up by more than a factor of N , a situation entitled
super-linear speedup. To experiment with this, use the job description here (`-L a:100:100,b:100:100,c:100:100`) with a small
cache (`-M 50`) to create three jobs. Run this on systems with 1, 2,
and 3 CPUs (`-n 1, -n 2, -n 3`). Now, do the same, but with a
larger per-CPU cache of size 100. What do you notice about performance as the number of CPUs scales? Use -c to confirm your
guesses, and other tracing flags to dive even deeper.

`-n 1`: Finish time 300. The CPU's cache can only hold one process's working set size, which means the CPU needs to be continually warmed.
`-n 2`: Finish time 150. CPUs still need to be continually warmed, but the added CPU reduces runtime.
`-n 3`: Finish time 55. Each process is effectively given its own CPU, allowing for each one to stay warm and thus finish quicker.


>8. One other aspect of the simulator worth studying is the per-CPU
scheduling option, the -p flag. Run with two CPUs again, and this
three job configuration (`-L a:100:100,b:100:50,c:100:50`).
How does this option do, as opposed to the hand-controlled affinity
limits you put in place above? How does performance change as
you alter the ’peek interval’ (-P) to lower or higher values? How
does this per-CPU approach work as the number of CPUs scales?

Finish time: 100. Allowing for peeking and stealing jobs let CPU 1 not become idle while CPU 0 runs two jobs, letting every process finish faster. Setting the peek interval too low could lead to reduced performance, but setting it too high could lead to high idle times. Sometimes creating too many CPUs and a high peak rate could be bad due to CPUs becoming cold.

>9. Finally, feel free to just generate random workloads and see if you can predict their performance on different numbers of processors,
cache sizes, and scheduling options. If you do this, you’ll soon be
a multi-processor scheduling master, which is a pretty awesome
thing to be. Good luck!