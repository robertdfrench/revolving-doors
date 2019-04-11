#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>

#include "common.h"

int main(int argc, char** argv) {
	time_t t[2];

	char* path = "server.door";
	int door = open(path, O_RDONLY);
	if (door == -1) err(1, "Could not open door");

	door_arg_t args;
	args.data_ptr = calloc(nelem, elsize);
	args.data_size = nelem * elsize;
	args.desc_ptr = NULL;
	args.desc_num = 0;
	args.rbuf = args.data_ptr;
	args.rsize = args.rsize;

	t[0] = time(NULL);
	for(int i = 0; i < iterations; i++) {
		int result = door_call(door, &args);
		if (result == -1) err(1, "Could not call door");
	}
	t[1] = time(NULL);

	printf("Message size: %dKB\n", (nelem * elsize)/1024);
	printf("Throughput: %f doors/sec\n", ((float) iterations)/(t[1] - t[0]));
	return 0;
}
