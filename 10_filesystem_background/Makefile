include ../lib.mk

test: clean server.door ## Create a place for the door to exist
	ls -AhlF server.door
	./server
	ls -AhlF server.door

server.door: server
	./server

server: server.c
	cc server.c -o $@

clean:
	rm -f server server.door
