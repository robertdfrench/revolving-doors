test: client server
	./server &
	sleep 1
	time ./client

server: server.c
	cc server.c -o $@

client: client.c
	cc client.c -o $@
