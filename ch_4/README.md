## THE ABSTRACTION: THE PROCESS
### Homework (Simulation)

This program, `process-run.py`, allows you to see how process states
change as programs run and either use the CPU (e.g., perform an add
instruction) or do I/O (e.g., send a request to a disk and wait for it to
complete). See the README for details.

Questions

>1. Run `process-run.py` with the following flags: `-l 5:100,5:100`.
>What should the CPU utilization be (e.g., the percent of time the
>CPU is in use?) Why do you know this? Use the `-c` and `-p` flags to
>see if you were right.

 100%, because the chance of using the CPU was 100% for both processes.


>2. Now run with these flags: `./process-run.py -l 4:100,1:0`.
>These flags specify one process with 4 instructions (all to use the
>CPU), and one that simply issues an I/O and waits for it to be done.
>How long does it take to complete both processes? Use `-c` and `-p`
>to find out if you were right.

 It takes 11 time units to complete. The cpu process finishes in 4
 time units, the IO is started on the fifth, then blocked for 5
 time units (4 + 1 + 5), then finishes on the 11th time unit. 

>3. Switch the order of the processes: `-l 1:0,4:100`. What happens
>now? Does switching the order matter? Why? (As always, use `-c`
>and `-p` to see if you were right)

 Yes, it does matter. Because the IO started first, the CPU can be
 utilized by the second process. This means the IO is started on the
 1st unit, then becomes blocked while the second process finishes its
 4 instructions. One more time unit for the blocked IO, then it terminates.

>4. We’ll now explore some of the other flags. One important flag is
>`-S`, which determines how the system reacts when a process issues
>an I/O. With the flag set to `SWITCH ON END`, the system
>will NOT switch to another process while one is doing I/O, instead
>waiting until the process is completely finished. What happens
>when you run the following two processes (`-l 1:0,4:100
>-c -S SWITCH ON END`), one doing I/O and the other doing CPU
>work?

 It will finish in 11 time units, because the second process was not
 able to utilize the CPU while the first process was blocked.

>5. Now, run the same processes, but with the switching behavior set
>to switch to another process whenever one is WAITING for I/O (`-l
>1:0,4:100 -c -S SWITCH ON IO`). What happens now? Use `-c`
>and `-p` to confirm that you are right.

 It finishes in 7 time units, because the CPU was able to be utilized
 while the first process was blocked.

>6. One other important behavior is what to do when an I/O com
>pletes. With `-I IO RUN LATER`, when an I/O completes, the process
>that issued it is not necessarily run right away; rather, whatever
>was running at the time keeps running. What happens when
>you run this combination of processes? (`./process-run.py -l
>3:0,5:100,5:100,5:100 -S SWITCH ON IO -c -p -I
>IO RUN LATER`) Are system resources being effectively utilized?

 No, they are not being utilized effectively. IO calls could be
 called one after another to allow for the IO to complete while
 a separate process also completes, but each IO call after the first
 has to wait for the other two processes to completely before starting
 its other ones.

>7. Now run the same processes, but with `-I IO RUN IMMEDIATE` set,
>which immediately runs the process that issued the I/O. How does
>this behavior differ? Why might running a process that just completed
>an I/O again be a good idea?

 It completes in less time, because the IOs being called earlier allow
 for other processes to start as well, instead of each IO waiting for
 a process to finish.

>8. Now run with some randomly generated processes using flags `-s
>1 -l 3:50,3:50` or `-s 2 -l 3:50,3:50` or `-s 3 -l 3:50,
>3:50`. See if you can predict how the trace will turn out. What happens
>when you use the flag `-I IO RUN IMMEDIATE` versus that
>flag `-I IO RUN LATER`? What happens when you use the flag `-S
>SWITCH ON IO` versus `-S SWITCH ON END`?

 Run immediate should allow for faster completion since resources can be
 utilized more effectively. Switching on end means that the CPU can not be utilized
 even when a process is blocked from an IO, making it complete in longer time.

