help: #: Show this help menu
	@echo "USAGE:\n"
	@cat Makefile \
		| grep '#:' \
		| grep -v grep \
		| awk -F':' '{print $$1,$$3 }' \
		| sort

start: bin/dchat #: Start the dchat server
	./bin/dchat server

follow: bin/dchat #: Follow the conversation
	./bin/dchat follow

post: bin/dchat #: Post a new message to the chat
	./bin/dchat post

bin/dchat: main.c bin/.dir
	$(CC) main.c -o $@

bin/.dir:
	mkdir -p bin
	touch $@

clean: #: Clean up local stuff
	rm -rf bin
