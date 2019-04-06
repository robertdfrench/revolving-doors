BEGIN	{ prev="undefined"; this="undefined"; post="undefined" }
NR==1	{
		this=$0
	}
NR>=2	{
		post=$0
		print prev, this, post
		prev=this
		this=post
	}
END	{
		post="undefined"
		print prev, this, post
	}
