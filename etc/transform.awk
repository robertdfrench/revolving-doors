$1 == "undefined" {
	nav="[Next](../" $3 ")"
}
$1 != "undefined" && $3 != "undefined" {
	nav="[Previous](../" $1 ") | [Next](../" $3 ")"
}
$3 == "undefined" {
	nav="[Previous](../" $1 ")"
}
{ print "awk -v nav=\"" nav "\" -f etc/update.awk " $2 " > /tmp/transform && mv /tmp/transform " $2 }
