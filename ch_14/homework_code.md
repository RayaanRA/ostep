## Homework (Code)

In this homework, you will gain some familiarity with memory allo-
cation. First, you’ll write some buggy programs (fun!). Then, you’ll use
some tools to help you find the bugs you inserted. Then, you will realize
how awesome these tools are and use them in the future, thus making
yourself more happy and productive. The tools are the debugger (e.g.,
gdb) and a memory-bug detector called valgrind [SN05].

Questions

>1. First, write a simple program called null.c that creates a pointer
to an integer, sets it to NULL, and then tries to dereference it. Com-
pile this into an executable called null. What happens when you
run this program?

Segmentation fault (core dumped)

>2. Next, compile this program with symbol information included (with
the -g flag). Doing so let’s put more information into the exe-
cutable, enabling the debugger to access more useful information
about variable names and the like. Run the program under the
debugger by typing gdb ./null and then, once gdb is running,
typing run. What does gdb show you?

```
Program received signal SIGSEGV, Segmentation fault.
0x000055555555513d in main () at null.c:6
6               *pointer = 5;
```

>3. Finally, use the valgrind tool on this program. We’ll use memcheck
that is a part of valgrind to analyze what happens. Run this by
typing in the following: valgrind --leak-check=yes ./null.
What happens when you run this? Can you interpret the output
from the tool?

```
==1263== Memcheck, a memory error detector
==1263== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==1263== Using Valgrind-3.26.0 and LibVEX; rerun with -h for copyright info
==1263== Command: ./null
==1263==
==1263== Invalid write of size 4
==1263==    at 0x400113D: main (null.c:6)
==1263==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==1263==
==1263==
==1263== Process terminating with default action of signal 11 (SIGSEGV)
==1263==  Access not within mapped region at address 0x0
==1263==    at 0x400113D: main (null.c:6)
==1263==  If you believe this happened as a result of a stack
==1263==  overflow in your program's main thread (unlikely but
==1263==  possible), you can try to increase the size of the
==1263==  main thread stack using the --main-stacksize= flag.
==1263==  The main thread stack size used in this run was 8388608.
==1263==
==1263== HEAP SUMMARY:
==1263==     in use at exit: 0 bytes in 0 blocks
==1263==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==1263==
==1263== All heap blocks were freed -- no leaks are possible
==1263==
==1263== For lists of detected and suppressed errors, rerun with: -s
==1263== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault (core dumped)
```

>4. Write a simple program that allocates memory using malloc() but
forgets to free it before exiting. What happens when this program
runs? Can you use gdb to find any problems with it? How about
valgrind (again with the --leak-check=yes flag)?

The program returns normally.

`gdb`:  
```
[Inferior 1 (process 1499) exited normally]
```

`valgrind`:  
```
==1503== Memcheck, a memory error detector
==1503== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==1503== Using Valgrind-3.26.0 and LibVEX; rerun with -h for copyright info
==1503== Command: ./four
==1503==
==1503==
==1503== HEAP SUMMARY:
==1503==     in use at exit: 4 bytes in 1 blocks
==1503==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==1503==
==1503== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==1503==    at 0x484B80F: malloc (vg_replace_malloc.c:447)
==1503==    by 0x400115E: main (four.c:5)
==1503==
==1503== LEAK SUMMARY:
==1503==    definitely lost: 4 bytes in 1 blocks
==1503==    indirectly lost: 0 bytes in 0 blocks
==1503==      possibly lost: 0 bytes in 0 blocks
==1503==    still reachable: 0 bytes in 0 blocks
==1503==         suppressed: 0 bytes in 0 blocks
==1503==
==1503== For lists of detected and suppressed errors, rerun with: -s
==1503== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

>5. Write a program that creates an array of integers called data of size
100 using malloc; then, set data[100] to zero. What happens
when you run this program? What happens when you run this
program using valgrind? Is the program correct?

The program runs normally.  
`valgrind`:  
```
==1818== Memcheck, a memory error detector
==1818== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==1818== Using Valgrind-3.26.0 and LibVEX; rerun with -h for copyright info
==1818== Command: ./five
==1818==
==1818== Invalid write of size 4
==1818==    at 0x400118D: main (five.c:6)
==1818==  Address 0x4a831d0 is 0 bytes after a block of size 400 alloc'd
==1818==    at 0x484B80F: malloc (vg_replace_malloc.c:447)
==1818==    by 0x400117E: main (five.c:5)
==1818==
==1818==
==1818== HEAP SUMMARY:
==1818==     in use at exit: 0 bytes in 0 blocks
==1818==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==1818==
==1818== All heap blocks were freed -- no leaks are possible
==1818==
==1818== For lists of detected and suppressed errors, rerun with: -s
==1818== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

There was an invalid write, the program is not correct as it accesses out of bounds.

>6. Create a program that allocates an array of integers (as above), frees
them, and then tries to print the value of one of the elements of
the array. Does the program run? What happens when you use
valgrind on it?

The program runs, but outputs a garbage value.  
`valgrind`:
```
==1920== Memcheck, a memory error detector
==1920== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==1920== Using Valgrind-3.26.0 and LibVEX; rerun with -h for copyright info
==1920== Command: ./six
==1920==
==1920== Invalid read of size 4
==1920==    at 0x40011B3: main (in /mnt/c/Users/Rayaan/documents/repos/ostep/ch_14/six)
==1920==  Address 0x4a83040 is 0 bytes inside a block of size 400 free'd
==1920==    at 0x484EB2C: free (vg_replace_malloc.c:990)
==1920==    by 0x40011AE: main (in /mnt/c/Users/Rayaan/documents/repos/ostep/ch_14/six)
==1920==  Block was alloc'd at
==1920==    at 0x484B80F: malloc (vg_replace_malloc.c:447)
==1920==    by 0x400119E: main (in /mnt/c/Users/Rayaan/documents/repos/ostep/ch_14/six)
==1920==
0
==1920==
==1920== HEAP SUMMARY:
==1920==     in use at exit: 0 bytes in 0 blocks
==1920==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==1920==
==1920== All heap blocks were freed -- no leaks are possible
==1920==
==1920== For lists of detected and suppressed errors, rerun with: -s
==1920== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

>7. Now pass a funny value to free (e.g., a pointer in the middle of the
array you allocated above). What happens? Do you need tools to
find this type of problem?

```
free(): invalid pointer
Aborted (core dumped)
```

A tool is not needed to find this type of problem.

>8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to
store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does
such a vector perform? How does it compare to a linked list? Use
valgrind to help you find bugs.

>9. Spend more time and read about using gdb and valgrind. Know-
ing your tools is critical; spend the time and learn how to become
an expert debugger in the UNIX and C environment.