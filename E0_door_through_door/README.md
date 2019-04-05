# Pass a door through a door
*This is really the killer feature*

In this lesson, we show how to use the `door_return` call to pass an open door
descriptor to another process. This can be a bit weird to wrap your head around,
but it is an amazing capability.

Consider three processes: A, B, and C. Process B creates a door which can be
opened by A, then process C creates a door which can be opened by B. When A
performs `door_call` on B's door, B can `door_return` its descriptor to C. When
A's `door_call` completes, A will have a new open door descriptor pointing to
the door that C opened for B. This allows A and C to communicate without
explicit knowledge of one another's identities.

*But why not let A and C communicate directly?*

In this situation, process B has the opportunity to decide whether A and C
should communicate. For example, B may require some form of credentials from A
before allowing access to C. This allows C to focus on doing what it does best,
leaving it up to B to focus on the authentication question.

As another example, B could act as a sortof router: inspecting the requests
coming from A before handing A a door descriptor either to C or some other door
server process as appropriate.

This is weird, and it's worth thinking about slowly.
