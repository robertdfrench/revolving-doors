#include <door.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char** argv) {

	// Open the door
        int door = open("server.door", O_RDONLY);
        if (door == -1) {
                perror("Could not open door");
                exit(1);
        }

	// Call the server's "answer" function
	int result = door_call(door, NULL);
	if (result == -1) {
		perror("My door request could not be placed");
		exit(1);
	}

        return 0;
}
