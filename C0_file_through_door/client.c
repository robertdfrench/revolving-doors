#include <door.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
	time_t t[2];

	char* path = "server.door";
	int server = open(path, O_RDONLY);
	if (server == -1) err(1, "Could not open door");

	door_arg_t args = {0};

	int result = door_call(server, &args);
	if (result == -1) err(1, "Could not call the dang ole door man");

	door_desc_t* w_descriptor = args.desc_ptr;
	int file = w_descriptor->d_data.d_desc.d_descriptor;

	char data[128];
	read(file, data, 128);

	printf("data: %.*s\n", 128, data);
	return 0;
}
