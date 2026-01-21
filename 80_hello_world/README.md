[Previous](.././40_knock_knock/) | [Next](.././90_automatic_thread_management/)

# Hello, World!
*Send a message through a door to another process*

In this lesson, we demonstrate how to pass a string through a door into the
server process, and return a string back to the client. These being polite
programs, they will exchange pleasantries:

> client: "Hello, World!"

> server: "Well hello yourself!"

```mermaid
sequenceDiagram
    participant client
    participant server.door
    participant server
    participant void answer()

    server ->> server.door: open()

    server ->> void answer(): door_create()

    server ->> server.door: fattach(answer)

    server.door --> void answer(): connected

    note over client: ./client
    activate client
    client ->> server.door: open()
    client ->> void answer(): door_call("Hello World!")
    deactivate client

    activate void answer()
    void answer() ->> client: door_return("Well hello, yourself!")
    deactivate void answer()
```

What we provide to the doors library is not this data, but rather the
addresses and lengths of these two strings. For the client, the structure that
holds these addresses and lengths is a `door_arg_t` and it looks like this:

```c
// from DOOR_CALL(3C) in the illumos manual
typedef struct {
        char            *data_ptr;      /* Argument/result data */
        size_t          data_size;      /* Argument/result data size */
        door_desc_t     *desc_ptr;      /* Argument/result descriptors */
        uint_t          desc_num;       /* Argument/result num descriptors */
        char            *rbuf;          /* Result area */
        size_t          rsize;          /* Result size */
} door_arg_t;
```

The address of our greeting will go in `data_ptr`, and its length will go in
`data_size`. We will discuss the other fields later.

Once we have this struct configured, we pass it to the doors library like so:

```c
door_call(door, &args);
```

Take it for a spin with `make test` and let's see what comes out!

## Check for Understanding
1. Why do we pass a pointer to `args` instead of `args` itself?
1. Before we called `door_call`, the value of `args.data_ptr` was equal to `greeting`. Will this be the case once `door_call` returns?
