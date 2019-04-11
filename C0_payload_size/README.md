[Previous](.././A0_return_sizes/) | [Next](.././E0_door_through_door/)

# What all can we fit through a door?
Not all doors are created equal. On SmartOS, new doors can handle about 1.7MB of
data per call. On OpenIndiana, it is less than 1MB by default. However, we can
change this size.

Using the `door_setparam` system call, we can grow or shrink the door width as
necessary to allow for consistent message sizes. This allows us to measure, as
we do in this lesson, how long it takes (roughly) to pass 5,000 1MB messages
from a client to a server using `door_call`.
