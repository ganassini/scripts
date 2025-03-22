#!/bin/sh
#
# Print what a bash [exit code] means

ec_list_path=$HOME/"scripts/exit_codes.txt"

usage() {
	echo ""
	echo "Usage: err [exit code]"
	echo ""
}

if [ $# -ne 1 ];then
	usage
	exit 1
else
	ec_description=$(awk -v arg="$1" -v ORS=" " '{ for (i=1;i<=NF;i++) { if ($i == arg) print $0; break} }' $ec_list_path );
	if [ ! -z "$ec_description" -a "$ec_description" != " " ];then
		echo ""
		echo "$ec_description"
		echo ""
		exit 0
	else
		echo "Non existant exit code."
		exit 1
	fi
fi
