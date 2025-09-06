start: bin/dchat
	./bin/dchat server

follow: bin/dchat
	./bin/dchat follow

post: bin/dchat
	./bin/dchat post

bin/dchat: main.c bin/.dir
	$(CC) main.c -o $@

bin/.dir:
	mkdir -p bin
	touch $@

clean:
	rm -rf bin
