#include <door.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>

#include "common.h"

void answer(void* cookie, char* args, size_t nargs, door_desc_t* descriptors, uint_t ndescriptors) {
	door_return(cookie, nelem * elsize, NULL, 0);
}

int main() {
	char* path = "server.door";

        int door = door_create(&answer, calloc(nelem, elsize), 0);
        if (door == -1) err(1, "Handle cannot be attached to door");

	int fd = open(path, O_RDWR|O_CREAT|O_EXCL, 0400);
	if (fd < 0) err(1, "Could not create a new file for the door");

        int attachment = fattach(door, path);
        if (attachment == -1) err(1, "Could not attach door to server.door");

        printf("%s will remain attached to this process for 1 hour\n", path);

	sleep(3600);

	return 0;
}
