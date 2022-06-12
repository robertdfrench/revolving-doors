include ../etc/lib.mk

test: test_door test_socket ## Compare performance of Doors and Sockets

test_door: clean door_client door_server.door ## Run Door Benchmark
	$(call emphasize, Exchange pleasantries with the door_server)
	./door_client
	kill `cat door_server.pid`

test_socket: clean socket_client socket_server.sock ## Run Socket Benchmark
	$(call emphasize, Exchange pleasantries with the socket_server)
	./socket_client
	kill `cat socket_server.pid`

door_server.door: door_server.pid
	while [ ! -e $@ ]; do sleep 1; done

door_server.pid: door_server
	./door_server &; echo $$! > $@

door_server: door_server.c
	$(CC) door_server.c -o $@

door_client: door_client.c
	$(CC) door_client.c -o $@

socket_server.sock: socket_server.pid
	while [ ! -e $@ ]; do sleep 1; done

socket_server.pid: socket_server
	./socket_server &; echo $$! > $@

socket_client: socket_client.c
	$(CC) socket_client.c -o $@

socket_server: socket_server.c
	$(CC) socket_server.c -o $@
