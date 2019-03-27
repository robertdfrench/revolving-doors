include ../lib.mk

test: clean server
	$(call emphasize, Execute the demo program)
	./server

server: server.c
	$(call emphasize, Compile the demo program)
	$(CC) $< -o $@

clean:
	rm -f server
