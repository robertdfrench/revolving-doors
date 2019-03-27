include ../lib.mk

test: clean client proxy.door
	$(call emphasize, Exchange a door through the proxy)
	./client
	$(call emphasize, Cleanup both server and proxy processes)
	kill `cat server.pid`
	kill `cat proxy.pid`

proxy.door: proxy.pid
	$(call emphasize, Wait for the proxy door to become available)
	while [ ! -e $@ ]; do sleep 1; done

proxy.pid: proxy server.door
	$(call emphasize, Background the proxy server)
	./proxy &; echo $$! > $@

proxy: proxy.c
	$(CC) proxy.c -o $@

server.door: server.pid
	while [ ! -e $@ ]; do sleep 1; done

server.pid: server
	./server &; echo $$! > $@

server: server.c
	$(CC) server.c -o $@

client: client.c
	$(CC) client.c -o $@

clean:
	rm -f server.door server.pid server
	rm -f proxy.door proxy.pid proxy
	rm -f client
