#include <err.h>
#include <fcntl.h>
#include <sys/stat.h>
// New headers for this lesson
#include <unistd.h>
#include <stdio.h>

int main() {
	char* path = "server.door";

	// Attempt to create a file at 'path'
	int fd = open(path, O_RDWR|O_CREAT|O_EXCL, 0400);
	if (fd < 0) err(1, "Could not create a new file for the door");

	// Leave this server running until `make test` is done with it.
	printf("Waiting in the background...\n");
	sleep(3600);

	return 0;
}
