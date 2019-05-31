[Previous](.././90_automatic_thread_management/) | [Next](.././A0_result_parameters/)

# Preserving the main thread
So far in this tutorial, we have been following this sort of pattern with our
main server threads:

1. Start up
1. Create a door
1. Sleep for an hour
1. Exit

However, this has the undesireable side effect that we leave this main thread
sitting idle, while other threads must be created to respond to `door_call`
invocations. It turns out that `door_return` has an additional property that we
have not discussed before: if you invoke it from a thread *not* currently
responding to a door request, that thread will halt and the operating system
will make it availble to handle door requests in the future. Now our
[server.c](server.c) can follow this pattern:

1. Start up
1. Create a door
1. `door_return` # chill and wait for door requests to come in.

## Check for Understanding
1. This lesson also launches three client binaries to invoke `door_call` at the same time. Do you see thread #1 responding to door calls now? What changed?
