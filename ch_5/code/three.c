#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

	pid_t pid = fork();
	if (pid == -1) {
		printf("Error forking\n");
		exit(1);
	}

	if (pid == 0) {
		printf("hello\n");
	} else {
		int status;
		waitpid(pid, &status, 0);
		printf("goodbye\n");
	}

	return 0;
}