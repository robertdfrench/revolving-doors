[Next](../v2)
# illumos door chat
This chat system is extremely simple. It does not provide an interactive,
IRC-like interface. You will need to use tmux or screen to set up multiple
terminals to run this.

Turning this into a friendly chat-style interface would make the program much
more complicated, and the code would be littered with tui stuff which isn't
relevant to our conversation about doors.

1. Start the server with `make server` in one window
1. Run `make follow` in another window to follow the conversation
1. Run `make post` in a third window and type some messages
