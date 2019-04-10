#include <err.h>
// New headers for this lesson
#include <fcntl.h>
#include <sys/stat.h>

// Create the file 'server.door' if it does not already exist
int main() {
	char* path = "server.door";

	// Attempt to create a file at 'path'
	int fd = open(path, O_RDWR|O_CREAT|O_EXCL, 0400);
	if (fd < 0) err(1, "Could not create a new file for the door");

	return 0;
}
