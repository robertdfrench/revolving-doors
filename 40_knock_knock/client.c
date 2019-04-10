#include <door.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>

int main(int argc, char** argv) {

	// Open the door
        int door = open("server.door", O_RDONLY);
        if (door == -1) err(1, "Could not open door");

	// Call the server's "answer" function
	int result = door_call(door, NULL);
	if (result == -1) err(1, "My door request could not be placed");

        return 0;
}
