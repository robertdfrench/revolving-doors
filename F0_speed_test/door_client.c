#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <err.h>

int main(int argc, char** argv) {
	char* path = "door_server.door";
	char* greeting = "Hello, World!";

	int door = open(path, O_RDONLY);
	if (door == -1) err(1, "Could not open door");

	door_arg_t args = {0};
	args.data_ptr = greeting;
	args.data_size = strlen(greeting);

	int result = door_call(door, &args);
	if (result == -1) err(1, "My door request could not be placed");

	// Let's see what's actually being returned
	printf("The total result size is %d bytes long\n", args.rsize);
	printf("The server's data response is %d bytes long\n", args.data_size);
	printf("The server's data response is: %s\n", args.data_ptr);
	return 0;
}
