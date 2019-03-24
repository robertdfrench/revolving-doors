#include <stdio.h>
#include <unistd.h>
#include <stropts.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
        struct stat buf;
	char* path = "server.door";

        if (stat(path, &buf) < 0) {
                int newfd;
                if ((newfd = creat(path, 0444)) < 0) {
                        perror("creat");
                        exit(1);
                }
                close(newfd);
        }

        fdetach(path);

	return 0;
}
