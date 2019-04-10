#include <err.h>
#include <stdlib.h>

int main() {
	char* path = "server.door";
	int result = 0; // Result of hypothetical system call

	// We'll be doing a *lot* of this
	if (result == -1) { // Check if the system call failed
		err(1, "The hypothetical system call failed!"); // Complain and die
	}

	return 0; // Exit cleanly if the system call succeeds
}
