include ../lib.mk

test: client server.door ## Send a greeting to the server
	$(call emphasize, Call a function in the backgrounded server process)
	./client
	kill `cat server.pid`

server.door: server.pid
	while [ ! -e $@ ]; do sleep 1; done

server.pid: server
	./server &; echo $$! > $@

server: server.c
	cc server.c -o $@

client: client.c
	cc client.c -o $@
