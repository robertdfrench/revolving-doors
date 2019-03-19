# Revolving Doors
Performance experiments with the Illumos Doors API

Run `make` on an Illumos system to time how long it takes for a client to invoke
a simple server handle one million times. The server function simply writes
`"hello world\0"` into the client buffer, so this is not an intricate call by
any means.
