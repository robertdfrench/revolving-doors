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
#define CHAT_ACTION_DOWN 3
#define CHAT_ACTION_STATS 4


static long long int last_message_id = 0;
static char last_message[255];
static uid_t last_message_author;


typedef struct chat_request {
	unsigned int action;
	char message[255];
	unsigned char message_length;
} chat_request_t;


typedef struct chat_ingress {
	uid_t author;
	char message[255];
} chat_ingress_t;


typedef struct chat_stats {
	long long int num_messages;
} chat_stats_t;


void action_post(chat_request_t* request) {
	// Store User ID of Client
	ucred_t* client_credentials = NULL;
	door_ucred(&client_credentials);
	last_message_author = ucred_getruid(client_credentials);
	ucred_free(client_credentials);

	// Store Message
	strncpy(last_message, request->message, 255);
	char* line_end = strchr(last_message, '\n');
	*line_end = 0;
	

	// Store next id
	last_message_id++;

	printf("POST: [%d | %d | %s]\n",
		last_message_author,
		last_message_id,
		last_message);
	door_return(NULL, 0, NULL, 0);
}

void action_stats() {
	ucred_t* client_credentials = NULL;
	door_ucred(&client_credentials);
	uid_t caller_id = ucred_getruid(client_credentials);
	ucred_free(client_credentials);

	printf("STATS: [%d]\n", caller_id);

	if (caller_id == 0) {
		chat_stats_t stats;
		stats.num_messages = last_message_id;
		door_return((char*)&stats, sizeof(chat_stats_t), NULL, 0);
	} else {
		door_return(NULL, 0, NULL, 0);
	}
}

void action_await() {
	int current_message_id = last_message_id;
	printf("AWAIT: [%d]\n", current_message_id);
	
	while(current_message_id == last_message_id) {
		sched_yield();
	}

	chat_ingress_t ingress;
	ingress.author = last_message_author;
	strncpy(ingress.message, last_message, 255);

	door_return((char*)&ingress, sizeof(chat_ingress_t), NULL, 0);
}

void action_down() {
	ucred_t* client_credentials = NULL;
	door_ucred(&client_credentials);
	uid_t caller_id = ucred_getruid(client_credentials);
	ucred_free(client_credentials);

	printf("DOWN: [%d]\n", caller_id);

	if (caller_id == 0) {
		exit(0);
	} else {
		door_return(NULL, 0, NULL, 0);
	}
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
		case CHAT_ACTION_DOWN: action_down(); break;
		case CHAT_ACTION_STATS: action_stats(); break;
		default: action_invalid();
	}
}

int server_main(int argc, char** argv) {
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

int client_await() {
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

		struct passwd* pw = getpwuid(ingress->author);

		printf("%s: %s\n", pw->pw_name, ingress->message);
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

int admin_down() {
	int fd = open(DOOR_PATH, 'r');
	chat_request_t request;
	request.action = CHAT_ACTION_DOWN;

	door_arg_t params;
	params.data_ptr = (char*)&request;
	params.data_size = sizeof(chat_request_t);
	params.desc_ptr = NULL;
	params.desc_num = 0;
	params.rbuf = NULL;
	params.rsize = 0;

	door_call(fd, &params);
	return 0;
}

int admin_stats() {
	int fd = open(DOOR_PATH, 'r');
	chat_request_t request;
	request.action = CHAT_ACTION_STATS;

	door_arg_t params;
	params.data_ptr = (char*)&request;
	params.data_size = sizeof(chat_request_t);
	params.desc_ptr = NULL;
	params.desc_num = 0;
	params.rbuf = NULL;
	params.rsize = 0;

	door_call(fd, &params);
	if (params.rbuf == NULL) err(1, "dchatd unavailable");

	chat_stats_t* stats = (chat_stats_t*)params.rbuf;
	printf("Total Messages: %lld\n", stats->num_messages);

	return 0;
}

int client_main(int argc, char** argv) {
	if (argc < 2) {
		err(1, "Must specify a subcommand");
	}

	switch (argv[1][0]) {
		case 'w': client_post(); break;
		case 'r': client_await(); break;
		default: err(1, "Unknown subcommand");
	}

	return 0;
}

int admin_main(int argc, char** argv) {
	if (argc < 2) {
		err(1, "Must specify a subcommand");
	}

	switch (argv[1][0]) {
		case 'd': admin_down(); break;
		case 's': admin_stats(); break;
		default: err(1, "Unknown subcommand");
	}

	return 0;
}

int main(int argc, char** argv) {
	if (strcmp(argv[0], "dchatd") == 0) {
		return server_main(argc, argv);
	} else if (strcmp(argv[0], "dchatadm") == 0) {
		return admin_main(argc, argv);
	} else {
		return client_main(argc, argv);
	}
}
