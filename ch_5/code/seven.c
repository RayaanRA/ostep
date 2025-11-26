#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	pid_t pid = fork();
	if (pid == -1) {
		printf("Error forking\n");
		exit(1);
	}

	if (pid == 0) {
		close(STDOUT_FILENO);
		printf("hello\n");
	}

	return 0;
}