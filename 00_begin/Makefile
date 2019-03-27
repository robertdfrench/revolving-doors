include ../lib.mk

test: server
	$(call emphasize, Execute the demo program)
	./server

server: server.c
	$(call emphasize, Compile the demo program)
	$(CC) $< -o $@
