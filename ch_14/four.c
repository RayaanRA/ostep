#include <stdlib.h>

int main(void) {

	int* data = (int*) malloc(sizeof(int));
	*data = 5;

	return 0; // forget to free()
}