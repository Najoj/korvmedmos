#!/bin/bash

BANOR="banor"

# Slumpa bana
if [ $# == 0 ]; then
	L=$(wc -l $BANOR | sed s/$BANOR//g)
	R=$(expr $RANDOM % $L + 1)
	echo -en "$(head -n $R $BANOR | tail -n 1)"

# Ta bana från nummret i argument 1.
elif [ $# == 1 ]; then
	echo -en "$(head -n $1 $BANOR | tail -n 1)"

# Ta bana ur fil från argument 1 och banan från nummret i argument 2
elif [ $# == 2 ]; then
	echo -en "$(head -n $2 $1 | tail -n 1)"
else
	exit -1
fi
exit 0
