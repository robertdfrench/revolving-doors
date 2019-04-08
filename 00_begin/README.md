[Next](.././10_filesystem_background/)

# Before we begin
We will set up a few conventions to help with this tutorial.

### Every lesson is its own project
Each lesson has its own source code, README, and [Makefile](Makefile). You can
build each one by entering its directory and typing `gmake test`. That will build
and execute the lesson to prove to you that it works. Your task is to read the
code and understand why it works. To make this easy, each lesson builds on the
prior one by adding the least possible amount of code.

### Error handling is everywhere
You will see blocks like this sprinkled throughout the source code:

```c
if (result == -1) {
	perror("A terrible thing has happened");
	exit(1);
}
```

This makes the code somewhat messier to read, but it is a great aide to
experimentation: as soon as you modify the lesson and something breaks, these
error messages will help you understand what system calls are failing, and the
associated man pages can help you figure out why.

### Some words of encouragement
Doors are unusual, but you'll get the hang of them. If you get confused or
frustrated, take a break and come back to it. They'll be here when you get back.

## Check for Understanding
1. What system header defines `perror`?
1. Why call `exit(1)` for an error instead of just returning normally?
