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
	char* greeting = "Hello, World!";
	char response[32];

        int door = open(path, O_RDONLY);
        if (door == -1) err(1, "Could not open door");

        door_arg_t args;
        args.data_ptr = greeting;
        args.rbuf = response;
        args.data_size = strlen(greeting);
        args.rsize = 32;
        args.desc_ptr = NULL;
        args.desc_num = 0;

	int result = door_call(door, &args);
	if (result == -1) err(1, "My door request could not be placed");

	// Doesn't it look better properly formatted?
	printf("The server's response is %d bytes long\n", args.data_size);
	printf("The server's response is: %.*s\n", args.data_size, response);
        return 0;
}
