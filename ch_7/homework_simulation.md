## Homework (Simulation)

This program, `scheduler.py`, allows you to see how different schedulers
perform under scheduling metrics such as response time, turnaround
time, and total wait time. See the `README` for details.

Questions

>1. Compute the response time and turnaround time when running
>three jobs of length 200 with the SJF and FIFO schedulers.

FIFO  
```
Here is the job list, with the run time of each job:
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )
```
Response Time: 0, 200, 400. Average: 200  
Turnaround Time: 200, 400, 600. Average: 400  

SJF  
Same as FIFO since all jobs are of the same length.  

>2. Now do the same but with jobs of different lengths: 100, 200, and 300.  

FIFO  
```
Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )
```
Response Time: 0, 100, 300. Average: 133.33  
Turnaround Time: 100, 300, 600. Average: 333.33  

SJF  
Same as FIFO since jobs already ran shortest first.  

>3. Now do the same, but also with the RR scheduler and a time-slice
>of 1.

Response Time: 0, 1, 2. Average: 1  
Turnaround Time: 298, 499, 600. Average: 465.67   

>4. For what types of workloads does SJF deliver the same turnaround
>times as FIFO?

When the job lengths are the same or FIFO already runs in shortest first.

>5. For what types of workloads and quantum lengths does SJF deliver
>the same response times as RR?

If the jobs are of same length and the time slice is equal to that length.

>6. What happens to response time with SJF as job lengths increase?
>Can you use the simulator to demonstrate the trend?

It will increase, as the later, longer jobs still have to wait for
the previous jobs that got longer as well.

>7. What happens to response time with RR as quantum lengths increase?
>Can you write an equation that gives the worst-case re-
>sponse time, given `N` jobs?

It increases since each job has to wait for a longer time slice.
Worst-case response time: `(N - 1) * (t)`, where `t` is the time slice.
`N - 1` because the worst-case would put the job at the last spot, and 
needs to wait that many time slices for each behind it.
