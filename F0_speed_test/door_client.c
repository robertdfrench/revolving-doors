#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <err.h>

#include "common.h"

int main(int argc, char** argv) {
	char* path = "door_server.door";
	int rc;
	int counter = 0;

	int door = open(path, O_RDONLY);
	if (door == -1) err(1, "Could not open door");

	for(int i = 0; i < ROUNDS; i++) {
		door_arg_t args = {0};
		args.data_ptr = ((char*) &counter);
		args.data_size = sizeof(int);
		args.rbuf = ((char*) &counter);
		args.rsize = sizeof(int);

		rc = door_call(door, &args);
		if (rc == -1) err(1, "My door request could not be placed");

		counter =  *((int*) args.data_ptr);
	};

	// Let's see what's actually being returned
	printf("Counter Value: %d\n", counter);
	return 0;
}
