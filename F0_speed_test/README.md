[Previous](.././E0_door_through_door/) | [Next](.././FF_finish/)

# Doors vs Sockets: Which are faster?
Doors get their speed by passing control from the client to the server
without giving up the current CPU timeslice. This means they can be
faster than sockets in certain situations. It all has to do with the
cost of switching back from the client to the server and back.

```mermaid
sequenceDiagram
    participant Other
    participant Server
    participant Client
    participant User

    Note right of Server: Using Doors

    User->>Client: request
    activate User
    activate Client
    Client->>Server: door_call
    deactivate Client                                      

    activate Server                    
    Server->>Client: door_return
    deactivate Server

    activate Client
    Client->>User: response
    deactivate Client
    deactivate User

    activate Other
    Other->>Other: unrelated work
    deactivate Other

    Note right of Server: Using Sockets

    User->>Client: request
    activate User
    activate Client
    Client-->>Server: write
    deactivate Client

    activate Other
    Other->>Other: unrelated work
    deactivate Other

    activate Server
    Client-->>Server: read
    Server-->>Client: write
    deactivate Server

    activate Other
    Other->>Other: unrelated work
    deactivate Other

    activate Client
    Server-->>Client: read
    Client->>User: response
    deactivate Client
    deactivate User
```
