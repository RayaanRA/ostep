## Homework (Code)

In this homework, you are to gain some familiarity with the process
management APIs about which you just read. Don’t worry – it’s even
more fun than it sounds! You’ll in general be much better off if you find
as much time as you can to write some code, so why not start now?

Questions

>1. Write a program that calls `fork()`. Before calling `fork()`, have the
>main process access a variable (e.g., `x`) and set its value to something
> (e.g., `100`). What value is the variable in the child process?
>What happens to the variable when both the child and parent change
>the value of `x`?

A: The value is the same as it is in the parent process. When both
the parent and child change the value of x, it seems that they now have
their own `x` variable.

>2. Write a program that opens a file (with the `open()` system call)
>and then calls `fork()` to create a new process. Can both the child
>and parent access the file descriptor returned by `open()`? What
>happens when they are writing to the file concurrently, i.e., at the
>same time?

A: Yes, both the parent and child can access the file descriptor
and read from it. `lseek()` was used so that both the parent and
child could read from the beginning of the file. Both the parent
and child can also write to the same file descriptor and their 
changes show depending on which ran first.

>3. Write another program using `fork()`. The child process should
>print “hello”; the parent process should print “goodbye”. You should
>try to ensure that the child process always prints first; can you do
>this without calling `wait()` in the parent?

A: The child process can be ensured to run first with the variations of
`wait()`. Doing this without `wait()` would be harder and require things
like condition variables and semaphores.

>4. Write a program that calls `fork()` and then calls some form of
>`exec()` to run the program `/bin/ls`. See if you can try all of the
>variants of `exec()`, including (on Linux) `execl()`, `execle()`,
>`execlp()`, `execv()`, `execvp()`, and `execvpe()`. Why do
>you think there are so many variants of the same basic call?

A: The man pages describe the difference with the 'l' and 'v' functions
as how the command-line arguments are specified, where the 'v' functions
are specified as a vector. Some other differences include how the executable
is searched, such a scenario being where there the specified filename does not
contain a slash (/) character (`execlp()`, `execvp()`, `execvpe`).

>5. Now write a program that uses `wait()` to wait for the child process
>to finish in the parent. What does `wait()` return? What happens if
>you use `wait()` in the child?

A: `wait()` returns the pid of the terminated child. Using `wait()`in 
the child returns `-1`.

>6. Write a slight modification of the previous program, this time
> using `waitpid()` instead of `wait()`. When would `waitpid()` be
>useful?

A: `waitpid()` could be useful when there are multiple children and the 
parent only needs to wait for one of them.

>7. Write a program that creates a child process, and then in the child
>closes standard output (`STDOUT_FILENO`). What happens if the child
>calls `printf()` to print some output after closing the descriptor?

A: It will not print, since the standard output was closed.

>8. Write a program that creates two children, and connects the
>standard output of one to the standard input of the other, using the
>`pipe()` system call.
