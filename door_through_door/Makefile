include ../lib.mk

test: client proxy.door ## Exchange a door through a proxy
	./client
	kill `cat server.pid`
	kill `cat proxy.pid`

proxy.door: proxy.pid
	sleep 1

proxy.pid: proxy server.door
	./proxy &; echo $$! > $@

proxy: proxy.c
	cc proxy.c -o $@

server.door: server.pid
	sleep 1

server.pid: server
	./server &; echo $$! > $@

server: server.c
	cc server.c -o $@

client: client.c
	cc client.c -o $@
