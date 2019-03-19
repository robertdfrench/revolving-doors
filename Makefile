.PHONY: help

help:
	@# Help Menu due to https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

test: client server.door ## Calculate total systime for 1 Million door_call()s
	time ./client

server.door: server
	./server &
	sleep 1

server: server.c
	cc server.c -o $@

client: client.c
	cc client.c -o $@
