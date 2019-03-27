include ../lib.mk

test: client server.door
	$(call emphasize, Calculate walltime for 1k door_calls)
	./client
	kill `cat server.pid`

server.pid: server
	./server &; echo $$! > $@

server.door: server.pid
	while [ ! -e $@ ]; do sleep 1; done

server: server.c
	$(CC) server.c -o $@

client: client.c
	$(CC) client.c -o $@
