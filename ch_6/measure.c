#define _GNU_SOURCE
#include <time.h>
#include <sched.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

	// system call
	int fd = open("text.txt", O_RDONLY);
	struct timeval start, end;
	int iterations = 100000;

	gettimeofday(&start, NULL);

	for (int i = 0; i < iterations; i++) {
		read(fd, NULL, 0);
	}
	gettimeofday(&end, NULL);
	printf("system call time: %f microseconds\n", (float) (((end.tv_sec - start.tv_sec) * 1000000)
									 + (end.tv_usec - start.tv_usec)) / (double) iterations);

	// context switch
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(sched_getcpu(), &set);
	sched_setaffinity(0, sizeof(cpu_set_t), &set);

	int pipefd_1[2];
	int pipefd_2[2];
	pipe(pipefd_1);
	pipe(pipefd_2);


	pid_t pid = fork();

	if (pid == 0) {
		char buf = 'r';
		close(pipefd_1[1]);
		close(pipefd_2[0]);

		for (int i = 0; i < iterations; i++) {
			read(pipefd_1[0], &buf, 1);
			write(pipefd_2[1], &buf, 1);
		}
		close(pipefd_1[0]);
		close(pipefd_2[1]);
		_exit(0);
	} else {
		gettimeofday(&start, NULL);

		char buf = 'r';
		close(pipefd_1[0]);
		close(pipefd_2[1]);

		for (int i = 0; i < iterations; i++) {
			write(pipefd_1[1], &buf, 1);
			read(pipefd_2[0], &buf, 1);
		}
		gettimeofday(&end, NULL);

	printf("context switch time: %f microseconds\n", (float) (((end.tv_sec - start.tv_sec) * 1000000)
														+ (end.tv_usec - start.tv_usec)) / (double) iterations / 2);

	close(pipefd_1[1]);
	close(pipefd_2[0]);

	}

	return 0;
}