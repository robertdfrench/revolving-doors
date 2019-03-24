#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char** argv) {
	char* path = "server.door";
	char* greeting = "Hello, World!";
	char response[32];

        int door = open(path, O_RDONLY);
        if (door == -1) {
                perror("Could not open door");
                exit(1);
        }

        door_arg_t args;
        args.data_ptr = greeting;
        args.data_size = strlen(greeting);
        args.desc_ptr = NULL;
        args.desc_num = 0;
        args.rbuf = response;
        args.rsize = 32;

	int result = door_call(door, &args);
	if (result == -1) {
		perror("Could not call door");
		exit(1);
	}

	printf("%s\n", response);
        return 0;
}
