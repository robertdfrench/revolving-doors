include ../lib.mk

test: server.door ## Send a greeting to the server
	ls -AhlF server.door
	kill `cat server.pid`

server.door: server.pid
	while [ ! -e $@ ]; do sleep 1; done

server.pid: server
	./server &; echo $$! > $@

server: server.c
	cc server.c -o $@
