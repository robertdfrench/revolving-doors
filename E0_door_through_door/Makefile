include ../lib.mk

test: client proxy.door ## Exchange a door through a proxy
	./client
	kill `cat server.pid`
	kill `cat proxy.pid`

proxy.door: proxy.pid
	while [ ! -e $@ ]; do sleep 1; done

proxy.pid: proxy server.door
	./proxy &; echo $$! > $@

proxy: proxy.c
	cc proxy.c -o $@

server.door: server.pid
	while [ ! -e $@ ]; do sleep 1; done

server.pid: server
	./server &; echo $$! > $@

server: server.c
	cc server.c -o $@

client: client.c
	cc client.c -o $@
