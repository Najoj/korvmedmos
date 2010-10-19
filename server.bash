#!/bin/bash

# Default board file.
BANOR="banor"

# Choosing pseudorandom board from default file
if [ $# == 0 ]; then
	L=$(wc -l $BANOR | sed s/$BANOR//g)
	R=$(expr $RANDOM % $L + 1)
	echo -en "$(head -n $R $BANOR | tail -n 1)"

# Choosing board from argument 1, from default file
elif [ $# == 1 ]; then
	echo -en "$(head -n $1 $BANOR | tail -n 1)"

# Choosing board from argument 2, from default argument 1 file.
elif [ $# == 2 ]; then
	echo -en "$(head -n $2 $1 | tail -n 1)"
else
	exit -1
fi

exit 0

# Format for board in input file:
# This board:
#   ####
#   #+ #
#   #$ #
#   #  #
#   ####
# becomes
#   ####\n#+ #\n#$ #\n#  #\n####\n
