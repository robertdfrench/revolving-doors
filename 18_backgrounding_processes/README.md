[Previous](.././10_filesystem_background/) | [Next](.././20_create_a_door/)

# Tricks for backgrounding processes with Make
Most of the exercises in this tutorial will start a server in the background
and run one or more client processes to interact with it. In order to prevent a
[vexation of zombies](https://wondermark.com/566/) from occurring, we need to
establish a pattern for cleaning up the server processes once we are done. Enter
[Make](https://www.gnu.org/software/make/).

In Make, like UNIX, everything is a file. So if we want to run a process in the
background and reap it later, we'll need to save its pid. We can accomplish this
in two phases:

### Starting a Background process
```Makefile
server.pid: server
	./server &; echo $$! > $@
```

this will expand into the following bash statements:

```bash
./server &
echo $! > server.pid
```

The `&`, of course, tells bash to run the `./server` command as a background
process, so control returns immediately. For convenience's sake, bash puts the
pid of the most recently backgrounded process in the variable `$!`. So to
preserve this value, we simply echo it to the `server.pid` file for later use.

### Reaping a process
After our test is complete, we simply `kill` whatever pid is listed in
`server.pid`:

```Makefile
test: server.door
	# blah blah do some tests with the server
	kill `cat server.pid`
```

This will first expand the contents of `server.pid` inline, and then send the
kill signal to that pid. What ties this story together is that, in our case, we
have defined `server.door` to be a file that depends on `server.pid` (that is,
the existence of a running server process) for its existence.

## Check for Understanding
1. Why should the `server.pid` target depend on `server`?
1. How many server processes will be created if we call `make test` twice?
1. How many will remain running afterwards?
