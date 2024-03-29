#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <err.h>
#include <stdint.h>
#include <stdbool.h>

int main() {
	char* path = "socket_server.sock";
        int rc;

	int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (socket_fd == -1) err(1, "Kernel refused our socket request");

	struct sockaddr_un address;
        memset(&address, 0, sizeof(struct sockaddr_un));
        address.sun_family = AF_UNIX;
        strncpy(address.sun_path, path, sizeof(address.sun_path) - 1);

        rc = bind(socket_fd, (const struct sockaddr*) &address, sizeof(struct sockaddr_un));
        if (rc == -1) err(1, "Could not bind socket to filesystem");

        rc = listen(socket_fd, 1);
        if (rc == -1) err(1, "Could not put socket in listening mode");

        while(true) {
            int client_fd = accept(socket_fd, NULL, NULL);
            if (client_fd == -1) err(1, "Could not accept new connection");

            while(true) {
                int buffer;
                rc = read(client_fd, (char*) &buffer, sizeof(int));
                if (rc == -1) break;

                buffer += 1;

                rc = send(client_fd, (char*) &buffer, sizeof(int), MSG_NOSIGNAL);
                if (rc == -1) break;
            }
            close(client_fd);
        }
        close(socket_fd);
	
	return 0;
}
