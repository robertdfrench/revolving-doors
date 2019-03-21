#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "common.h"

int main(int argc, char** argv) {
	char* path = "server.door";
        int door = open(path, O_RDONLY);
        if (door == -1) {
                perror("Could not open door");
                exit(1);
        }

        door_arg_t args;
        args.data_ptr = calloc(nelem, elsize);
        args.data_size = nelem * elsize;
        args.desc_ptr = NULL;
        args.desc_num = 0;
        args.rbuf = args.data_ptr;
        args.rsize = args.rsize;

	for(int i = 0; i < iterations; i++) {
		int result = door_call(door, &args);
		if (result == -1) {
			perror("Could not call door");
			exit(1);
		}
	}
        return 0;
}
