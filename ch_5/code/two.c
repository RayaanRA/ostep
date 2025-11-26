#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	int fd = open("two.txt", O_RDWR);
	if (fd == -1) {
		printf("Error opening file\n");
		exit(1);
	}

	int pid = fork();
	if (pid == -1) {
		printf("Error forking\n");
		exit(1);
	}

	if (pid == 0) {
		char child_buf[51];
		lseek(fd, 0, SEEK_SET);
		ssize_t bytes = read(fd, child_buf, 50);
		printf("Reading file from child:\n%s\n", child_buf);

		char child_write_buf[7] = "\nchild\n";
		write(fd, child_write_buf, 7);
		lseek(fd, 0, SEEK_SET);
		bytes = read(fd, child_buf, 50);
		printf("Reading file from child after modification:\n%s\n", child_buf);

	} else {
		char parent_buf[51];
		lseek(fd, 0, SEEK_SET);
		ssize_t bytes = read(fd, parent_buf, 50);
		printf("Reading file from parent:\n%s\n", parent_buf);

		char parent_write_buf[8] = "\nparent\n";
		write(fd, parent_write_buf, 8);
		lseek(fd, 0, SEEK_SET);
		bytes = read(fd, parent_buf, 50);
		printf("Reading file from parent after modification:\n%s\n", parent_buf);

	}

	return 0;
}