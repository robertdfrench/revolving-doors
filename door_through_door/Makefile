.PHONY: help

help:
	@# Help Menu due to https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

test: client proxy.door
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
