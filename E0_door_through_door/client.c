#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

int main(int argc, char** argv) {
	time_t t[2];

	char* path = "proxy.door";
        int proxy = open(path, O_RDONLY);
        if (proxy == -1) {
                perror("Could not open door");
                exit(1);
        }

        door_arg_t args;
        args.data_ptr = NULL;
        args.data_size = 0;
        args.desc_ptr = NULL;
        args.desc_num = 0;
        args.rbuf = NULL;
        args.rsize = 0;

	int result = door_call(proxy, &args);
	if (result == -1) {
		perror("Could not call door");
		exit(1);
	}

	door_desc_t* w_descriptor = args.desc_ptr;
	int server = w_descriptor->d_data.d_desc.d_descriptor;

	result = door_call(server, &args);
	if (result == -1) {
		perror("Could not call door");
		exit(1);
	}

	printf("data: %.*s\n", args.data_size, args.data_ptr);
        return 0;
}
