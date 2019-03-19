# Revolving Doors
Performance experiments with the Illumos Doors API

Run `make test` on an Illumos system to time how long it takes for a client to
invoke a simple server handle one million times. The server function simply
writes `"hello world\0"` into the client buffer, so this is not an intricate
call by any means.

### Sources
I am writing this because there seems to be so little about doors on the 
internet.

* ["Doors" in SolarisTM: Lightweight RPC using File Descriptors](http://www.kohala.com/start/papers.others/doors.html)
* [Door API Details](https://blogs.oracle.com/tucker/door-api-details)
* [DOOR_CREATE(3C)](https://illumos.org/man/3C/door_create)
* Chapter 15 "Doors" of *UNIX Network Programming, Volume 2, Second Edition: Interprocess Communications*, Prentice Hall, 1999, ISBN 0-13-081081-9.
