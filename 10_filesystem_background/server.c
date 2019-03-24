#include <stdio.h>
#include <unistd.h>
#include <stropts.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

// Create the file 'server.door' if it does not already exist
int main() {
        struct stat buf;
	char* path = "server.door";

	// Check to see if a file exists at 'path'
        if (stat(path, &buf) < 0) {
                int newfd;

		// No such file exists, so lets create it with 400 permissions
		// so that only we can access it
                if ((newfd = creat(path, 0400)) < 0) {
                        perror("Could not create a new file for the door");
                        exit(1);
                }
        }

	return 0;
}
