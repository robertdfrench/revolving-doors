#include <stdio.h>
#include <stdlib.h>

int main() {
	char* path = "server.door";
	int result = 0; // Result of hypothetical system call

	// We'll be doing a *lot* of this
	if (result == -1) { // Check if the system call failed
		perror("The hypothetical system call failed!"); // Complain
		exit(1); // die
	}

	return 0; // Exit cleanly if the system call succeeds
}
