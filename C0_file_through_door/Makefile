include ../etc/lib.mk

test: clean client server.door
	$(call emphasize, Obtain a file from the server)
	./client
	kill `cat server.pid`

server.door: server.pid
	while [ ! -e $@ ]; do sleep 1; done

server.pid: server
	./server &; echo $$! > $@

server: server.c
	$(CC) server.c -o $@

client: client.c
	$(CC) client.c -o $@
