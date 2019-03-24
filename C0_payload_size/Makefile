include ../lib.mk

test: client server.door ## Calculate walltime for 100k door_call()s
	./client
	kill `cat server.pid`

server.pid: server
	./server &; echo $$! > $@

server.door: server.pid
	sleep 1

server: server.c
	cc server.c -o $@

client: client.c
	cc client.c -o $@
