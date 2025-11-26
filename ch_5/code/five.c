#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	pid_t pid = fork();
	if (pid == -1) {
		printf("Error forking\n");
		exit(1);
	}

	if (pid == 0) {
		// int status;
		// int return_value = wait(&status);
	} else {
		printf("pid returned from fork(): %d\n", pid);
		int status;
		// int child_pid = wait(&status);
		int child_pid = waitpid(pid, &status, 0);
		printf("return value from wait(): %d\n", child_pid);
		
	}

	return 0;
}