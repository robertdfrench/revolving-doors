#include <door.h>
#include <stdio.h>
#include <unistd.h>
#include <stropts.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#include "common.h"

void handle(void* cookie, char* args, size_t nargs, door_desc_t* descriptors, uint_t ndescriptors) {
	char* secret = "s3cr3t_!nf0";
	door_return(secret, strlen(secret), NULL, 0);
}

int main() {
        struct stat buf;

	char* path = "server.door";

        int door = door_create(&handle, NULL, 0);
        if (door == -1) {
                perror("Handle cannot be attached to door");
                exit(1);
        }

        if (stat(path, &buf) < 0) {
                int newfd;
                if ((newfd = creat(path, 0444)) < 0) {
                        perror("creat");
                        exit(1);
                }
                close(newfd);
        }

        fdetach(path);

        int attachment = fattach(door, path);
        if (attachment == -1) {
                perror("Could not attach door to server.door");
                exit(1);
        }

        printf("%s will remain attached to this process for 1 hour\n", path);

	sleep(3600);

	return 0;
}
