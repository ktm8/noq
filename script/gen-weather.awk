# Usage: Generate weather.h data file
# Notes:
#   This script is meant to be piped with script/filter.awk

BEGIN {
	done = 0

	print "#include <vector>"
	print ""
	print "std::vector<int> weather = {"
}

END {
	print "};"
}

/===/ { done = 1 }
{ if (! done) print "\t" $0 "," }
