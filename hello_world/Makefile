include ../lib.mk

test: client server.door ## Send a greeting to the server
	./client
	kill `cat server.pid`

server.door: server.pid
	sleep 1

server.pid: server
	./server &; echo $$! > $@

server: server.c
	cc server.c -o $@

client: client.c
	cc client.c -o $@
