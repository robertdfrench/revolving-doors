include ../lib.mk

test: clean server.door
	$(call emphasize, Kill the server by dereferencing its pid)
	kill `cat server.pid`

server.door: server.pid
	$(call emphasize, Wait till the server creates the door file)
	while [ ! -e $@ ]; do sleep 1; done

server.pid: server
	$(call emphasize, Launch the server and retain its pid)
	./server &; echo $$! > $@

server: server.c
	$(CC) server.c -o $@ 
