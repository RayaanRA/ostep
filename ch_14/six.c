#include <stdlib.h>
#include <stdio.h>
int main(void) {

	int* data = (int*) malloc (100 * sizeof(int));
	free(&data[50]);
	// printf("%d\n", data[0]);

	return 0;
}