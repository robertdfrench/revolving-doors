#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	char* path = "server.door";
        int door = open(path, O_RDONLY);
        if (door == -1) {
                perror("Could not open door");
                exit(1);
        }

        char request[12];
        char reply[12];

        door_arg_t args;
        args.data_ptr = request;
        args.data_size = 12;
        args.desc_ptr = NULL;
        args.desc_num = 0;
        args.rbuf = reply;
        args.rsize = 12;

	for(int i = 0; i < 100000; i++) {
		int result = door_call(door, &args);
		if (result == -1) {
			perror("Could not call door");
			exit(1);
		}
	}
        printf(args.rbuf);
        printf("\n");
        return 0;
}
