#include <door.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>

void answer(void* cookie, char* args, size_t nargs, door_desc_t* descriptors, uint_t ndescriptors) {
	printf("Someone knocked on my door!\n");
	door_return(NULL, 0, NULL, 0);
}

int main() {
	char* path = "server.door";

        int door = door_create(&answer, NULL, 0);
        if (door == -1) err(1, "Handle cannot be attached to door");

	int fd = open(path, O_RDWR|O_CREAT|O_EXCL, 0400);
	if (fd < 0) err(1, "Could not create a new file for the door");

        int attachment = fattach(door, path);
        if (attachment == -1) err(1, "Could not attach door to server.door");

        printf("%s will remain attached to this process for 1 hour\n", path);

	sleep(3600);

	return 0;
}
