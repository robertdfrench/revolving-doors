include ../lib.mk

test: server.door ## Attach a door to the filesystem
	$(call emphasize, Show that the door exists. Notice its flags!)
	ls -AhlF server.door 
	kill `cat server.pid`

server.door: server.pid
	while [ ! -e $@ ]; do sleep 1; done

server.pid: server
	./server &; echo $$! > $@

server: server.c
	$(CC) server.c -o $@ 
