all: bin/dchatadm bin/dchatd bin/dchat

activate:
	PATH=`make _path` `make _shell` || true

_shell:
	@cat /etc/passwd | grep ${USER} | cut -d':' -f7

_path:
	@echo "$(PWD)/bin:$(PATH)"

bin/dchatadm: chat.c bin/.dir
	$(CC) chat.c -o $@

bin/dchatd: chat.c bin/.dir
	$(CC) chat.c -o $@

bin/dchat: chat.c bin/.dir
	$(CC) chat.c -o $@

bin/.dir:
	mkdir -p bin
	touch $@

clean:
	rm -rf bin
