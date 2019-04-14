[Previous](.././A0_return_sizes/) | [Next](.././E0_door_through_door/)

# How fast can we send data through a door?
The leading advantage of doors over other forms of IPC is their speed. Client
and server can communicate within the same time time slice, with no need to
block and wait for the OS to schedule the server thread. 
