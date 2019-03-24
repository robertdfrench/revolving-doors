include ../lib.mk

test: server.door ## Send a greeting to the server
	ls -AhlF server.door
	kill `cat server.pid`

server.door: server.pid
	sleep 1

server.pid: server
	./server &; echo $$! > $@

server: server.c
	cc server.c -o $@
