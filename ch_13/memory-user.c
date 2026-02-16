#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv) {
	
	if (argc < 2) {
		return 1;
	}

	int memory = atoi(argv[1]);
	size_t size = (size_t) memory * 1024 * 1024;
	char* array = (char*) malloc(size);

	if (array == NULL) return 1;

	printf("PID: %ld\n", (long) getpid());

	for (;;) {
		for (size_t i = 0; i < size; i++) {
			array[i]++;
		}
	}

	return 0;
}