include ../lib.mk

test: server.door ## Create a place for the door to exist
	ls -AhlF server.door

server.door: server
	./server &; echo $$! > $@

server: server.c
	cc server.c -o $@
