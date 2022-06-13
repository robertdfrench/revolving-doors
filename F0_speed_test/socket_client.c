#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <err.h>

int main(int argc, char** argv) {
	char* path = "socket_server.sock";
        int rc;

        int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (server_fd == -1) err(1, "Could not create socket");

        struct sockaddr_un address;
        memset(&address, 0, sizeof(struct sockaddr_un));
        address.sun_family = AF_UNIX;
        strncpy(address.sun_path, path, sizeof(address.sun_path) - 1);

        rc = connect(server_fd, (const struct sockaddr *) &address, sizeof(struct sockaddr_un));
        if (rc == -1) err(1, "Could not connect socket to server path");

        int counter = 0;
        while(counter < 1000000) {
            rc = write(server_fd, &counter, sizeof(int));
            if (rc == -1) err(1, "Failed to send counter to server");

            rc = read(server_fd, &counter, sizeof(int));
            if (rc == -1) err(1, "Failed to read new counter from server");
        }
        
        printf("Counter Value: %lld\n", counter);
	return 0;
}
