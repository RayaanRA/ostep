#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int x;
	x = 100;
	printf("Before forking, parent sets x to %d\n", x);
	int pid = fork();

	if (pid == -1) {
		printf("Error forking\n");
		exit(1);
	}

	if (pid == 0) {
		printf("Value of x in child: %d\n", x);
		x = 102;
		printf("Child has changed x to: %d\n", x);
	} else {
		x = 101;
		printf("Parent has changed x to: %d\n", x);
	}

	return 0;
}