## Homework (Simulation)

The program, malloc.py, lets you explore the behavior of a simple
free-space allocator as described in the chapter. See the README for
details of its basic operation.

Questions

>1. First run with the flags -n 10 -H 0 -p BEST -s 0 to generate 
a few random allocations and frees. Can you predict what alloc()/free() 
will return? Can you guess the state of the free list after
each request? What do you notice about the free list over time?

The free list gets bigger and bigger each time, as no coalescing is happening.
Once memory is freed, its beginning address is added back to the free list,
and is fragmented.

>2. How are the results different when using a WORST fit policy to
search the free list (-p WORST)? What changes?

The free list grows even bigger, as the largest chunks are used first,
and therefore increases the chance of fragmentation.

>3. What about when using FIRST fit (-p FIRST)? What speeds up
when you use first fit?

Since the free list seems to be in order of increasing size, smaller chunks
were used first. First fit increases speed.

>4. For the above questions, how the list is kept ordered can affect the
time it takes to find a free location for some of the policies. Use
the different free list orderings (-l ADDRSORT, -l SIZESORT+,
-l SIZESORT-) to see how the policies and the list orderings interact.

Sorting by highest size could make first fit behave like worst fit,
vice versa for best fit. However, worst fit and best fit would still
have to look through the entire free list.

>5. Coalescing of a free list can be quite important. Increase the number
of random allocations (say to -n 1000). What happens to larger
allocation requests over time? Run with and without coalescing
(i.e., without and with the -C flag). What differences in outcome do
you see? How big is the free list over time in each case? Does the
ordering of the list matter in this case?

Without coalescing, the free list becomes very large. With coalescing,
it remains small. In terms of order, sorting by address makes it easier
to coalesce, as adjacent chunks are already sorted. 

>6. What happens when you change the percent allocated fraction -P
to higher than 50? What happens to allocations as it nears 100?
What about as the percent nears 0?

At higher percents, free space runs out, while at lower percents,
free space remains highly available.

>7. What kind of specific requests can you make to generate a highly-
fragmented free space? Use the -A flag to create fragmented free
lists, and see how different policies and options change the organization 
of the free list.

Create very small allocation requests and use worst fit, so that the biggest chunk
will continuously be fragmented.