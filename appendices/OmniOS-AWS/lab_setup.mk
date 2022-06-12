revolving-doors/: /usr/bin/git /usr/bin/gcc /usr/bin/gmake
	/usr/bin/git clone https://github.com/robertdfrench/revolving-doors.git

/usr/bin/gcc:
	pkg install pkg:/developer/gcc9

/usr/bin/git:
	pkg install git

/usr/bin/gmake:
	pkg install pkg:/developer/build/gnu-make
