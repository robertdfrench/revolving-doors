[Previous](.././A0_result_parameters/) | [Next](.././E0_door_through_door/)

# Pass a file through a door
In this lesson, we show how to use the `door_return` call to pass an open file
descriptor to another process. This technique can allow a door server (running
as user A) to give read access to a door client (running as user B) even if the
filesystem permissions would not normally allow user B to read the file.

![file-through-door](file_through_door.svg)

This ability to pass open file descriptors to other processes is a standard (and
clever!) feature of UNIX IPC.
