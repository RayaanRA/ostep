#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

	int pipefd[2];
	if (pipe(pipefd) == -1) {
		printf("Error creating pipe\n");
		exit(1);
	}

	pid_t pid_1 = fork();
	if (pid_1 == -1) {
		printf("Error forking\n");
		exit(1);
	}



	if (pid_1 == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	} else {
		pid_t pid_2 = fork();
		if (pid_2 == -1) {
			printf("Error forking\n");
			exit(1);
		}
		if (pid_2 == 0) {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
	}


	return 0;
}