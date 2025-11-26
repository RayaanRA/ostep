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
		// execl("/bin/ls", "ls", NULL);
		char* args[] = {"ls", "-C", NULL};
		execv("/bin/ls", args);
	}

	return 0;
}