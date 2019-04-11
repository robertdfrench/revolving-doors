#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <err.h>

int main(int argc, char** argv) {
	char* path = "server.door";

	// The greeting we will send
	char* greeting = "Hello, World!";

	// A place to capture the server's response
	char response[32];

	int door = open(path, O_RDONLY);
	if (door == -1) err(1, "Could not open door");

	// Configure a "door argument" with our greeting and response
	door_arg_t args;
	args.data_ptr = greeting;
	args.rbuf = response;

	// Include their sizes so we know how many bytes to exchange!
	args.data_size = strlen(greeting);
	args.rsize = 32;

	// We are ignoring these for now, so lets zero them out
	args.desc_ptr = NULL;
	args.desc_num = 0;

	// Call the 'answer' function in server.c, passing it our greeting
	int result = door_call(door, &args);
	if (result == -1) err(1, "My door request could not be placed");

	// We expect the server's response to be printed:
	printf("%s\n", response);
	return 0;
}
