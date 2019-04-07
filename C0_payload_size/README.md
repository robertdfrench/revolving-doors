[Previous](.././A0_return_sizes/) | [Next](.././E0_door_through_door/)

# What all can we fit through a door?

It appears that the maximum message size is between 1,975 and 1,976 KB on
SmartOS, but between 983k and 984k on OpenIndiana. I think do not understand the
difference.

The throughtput (measured in `door_call()`/s) seems to drop linearly as a
function of the message size. I suspect the limit here is memory bandwidth,
which is a cool problem to have.
