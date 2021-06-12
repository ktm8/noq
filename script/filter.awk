# Usage: Extract weather data from ECA&D dataset
# Details:
#   Station: 11249, Orly, France
#   Source: 171642 - Mean temperatures (can be overrided)
#   Interval: 2000 - 2019
# 
# Acknowledgement: European Climate Assessment & Dataset (ECA&D)
#   Klein Tank, A.M.G. and Coauthors, 2002. Daily dataset of 20th-century
#   surface air temperature and precipitation series for the European
#   Climate Assessment.
#   Int. J. of Climatol., 22, 1441-1453.
#   Data and metadata available at http://www.ecad.eu

BEGIN {
	FS    = ","
	SOUID = ENVIRON["SOUID"]
	if (SOUID == 0)
		SOUID = 171642

	total = 0
	good  = 0
}

$1+0 == SOUID && $2 ~ /^20(0|1)/ {
	total += 1
	if ($4+0 == 0) good += 1
	print $3+0
}

END {
	print "==="
	print good " / " total
}
