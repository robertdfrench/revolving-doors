#include <stdio.h>
#include <err.h>
#include <door.h>
#include <fcntl.h>
#include <stropts.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <sched.h>
#include <ucred.h>
#include <pwd.h>
#include <sys/stat.h>


#define DOOR_PATH "/tmp/chat.door"

#define CHAT_ACTION_POST 1
#define CHAT_ACTION_AWAIT 2


static long long int last_message_id = 0;
static char last_message[255];


typedef struct chat_request {
	unsigned int action;
	char message[255];
	unsigned char message_length;
} chat_request_t;


typedef struct chat_ingress {
	char message[255];
} chat_ingress_t;


void action_post(chat_request_t* request) {
	// Store Message
	strncpy(last_message, request->message, 255);
	char* line_end = strchr(last_message, '\n');
	*line_end = 0;
	

	// Store next id
	last_message_id++;

	printf("POST: [%d | %s]\n",
		last_message_id,
		last_message);
	door_return(NULL, 0, NULL, 0);
}

void action_await() {
	int current_message_id = last_message_id;
	printf("AWAIT: [%d]\n", current_message_id);
	
	while(current_message_id == last_message_id) {
		sched_yield();
	}

	chat_ingress_t ingress;
	strncpy(ingress.message, last_message, 255);

	door_return((char*)&ingress, sizeof(chat_ingress_t), NULL, 0);
}

void action_invalid() {
	printf("INVALID\n");
	door_return(NULL, 0, NULL, 0);
}

// How many server procedures in gate check whether args is NULL?
void server_procedure(
	void* cookie,
	char* args,
	size_t nargs,
	door_desc_t* descriptors,
	uint_t ndescriptors
) {
	printf("+ ");

	chat_request_t* request = (chat_request_t*)args;

	if (request == NULL) {
		action_invalid();
	}
	
	switch (request->action) {
		case CHAT_ACTION_POST: action_post(request); break;
		case CHAT_ACTION_AWAIT: action_await(); break;
		default: action_invalid();
	}
}

int server_init() {
	printf("Start door server\n");
	int rc;

	int fd = door_create(&server_procedure, NULL, 0);
	if (fd == -1) err(1, "Could not create door");

	fdetach(DOOR_PATH);
	unlink(DOOR_PATH);

	rc = open(DOOR_PATH, O_RDWR|O_CREAT|O_EXCL, 0666);
	if (rc == -1) err(1, "Could not access door rendezvous file");

	rc = fattach(fd, DOOR_PATH);
	if (rc == -1) err(1, "Could not attach door to rendezvous file");

	rc = chmod(DOOR_PATH, 0666);
	if (rc == -1) err(1, "Couldn't make rendezvous file accessible");
	
	// Park this thread for future use as server thread
	return door_return(NULL, 0, NULL, 0);
}

int client_follow() {
	int fd = open(DOOR_PATH, 'r');

	chat_request_t request;
	request.action = CHAT_ACTION_AWAIT;

	door_arg_t params;

	chat_ingress_t* ingress = NULL;
	while(true) {
		params.data_ptr = (char*)&request;
		params.data_size = sizeof(chat_request_t);
		params.desc_ptr = NULL;
		params.desc_num = 0;
		params.rbuf = NULL;
		params.rsize = 0;

		door_call(fd, &params);
		if (params.rbuf == NULL) err(1, "Chat terminated");

		ingress = (chat_ingress_t*)params.rbuf;

		printf("%s\n", ingress->message);
	}

	return 0;
}

int client_post() {
	int fd = open(DOOR_PATH, 'r');
	chat_request_t request;

	door_arg_t params;

	while(true) {
		printf("> ");
		fflush(stdout);

		request.action = CHAT_ACTION_POST;
		params.data_ptr = (char*)&request;
		params.data_size = sizeof(chat_request_t);
		params.desc_ptr = NULL;
		params.desc_num = 0;
		params.rbuf = NULL;
		params.rsize = 0;

		if (fgets(request.message, 254, stdin) == NULL) {
			break;
		}

		door_call(fd, &params);
	}
	return 0;
}

int args_error() {
	fprintf(stderr, "Must specify one of the following subcommands: server, follow, post");
	return 1;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		return args_error();
	}

	char* subcommand = argv[1];

	if (strcmp(subcommand, "server") == 0) {
		return server_init();
	} else if (strcmp(subcommand, "follow") == 0) {
		return client_follow();
	} else if (strcmp(subcommand, "post") == 0) {
		return client_post();
	} else {
		return args_error();
	}
}
