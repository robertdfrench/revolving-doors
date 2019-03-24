# What all can we fit through a door?

It appears that the maximum message size is between 1,975 and 1,976 KB. The
throughtput (measured in `door_call()`/s) seems to drop linearly as a function
of the message size. I suspect the limit here is memory bandwidth, which is a
cool problem to have.
