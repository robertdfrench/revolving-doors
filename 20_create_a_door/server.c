#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stropts.h>
#include <fcntl.h>
#include <sys/stat.h>
// New headers for this lesson
#include <strings.h>
#include <door.h>

void answer(void* cookie, char* args, size_t nargs, door_desc_t* descriptors, uint_t ndescriptors) {
	printf("Someone knocked on my door!\n");
	// We return two empty sets: no data, no descriptors
	door_return(NULL, 0, NULL, 0);
}

int main() {
        struct stat buf;
	char* path = "server.door";

        if (stat(path, &buf) < 0) {
                int newfd;
                if ((newfd = creat(path, 0600)) < 0) {
                        perror("creat");
                        exit(1);
                }
                close(newfd);
        }

	// Unhook any other doors that might be loitering at this path
        fdetach(path);

	// Create a file descriptor which points to the 'answer' fucntion.
	// This is what a "door" is.
        int door = door_create(&answer, NULL, 0);
        if (door == -1) {
                perror("Handle cannot be attached to door");
                exit(1);
        }

	// Attach the door created above to 'server.door' on the filesystem
        int attachment = fattach(door, path);
        if (attachment == -1) {
                perror("Could not attach door to server.door");
                exit(1);
        }

	// Stick around at least long enough for this lesson to complete
        printf("%s will remain attached to this process for 1 hour\n", path);
	sleep(3600);

	return 0;
}
