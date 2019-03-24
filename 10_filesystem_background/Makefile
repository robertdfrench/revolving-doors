include ../lib.mk

test: server.door
	$(call emphasize, server.door exists as a normal file)
	ls -AhlF server.door
	$(call emphasize, We can rerun server. It is idempotent)
	./server
	ls -AhlF server.door

server.door: server
	$(call emphasize, Launch door server to create $@)
	./server

server: server.c
	cc server.c -o $@
