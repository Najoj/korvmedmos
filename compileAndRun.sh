#!/bin/bash

# You need the boost library for this program to compile, due to the client.
# 
# You also need boost bloom filter to run this program, which is not in the
# boost library.
# Get code:
#  svn co https://svn.boost.org/svn/boost/sandbox/bloom_filter/trunk/
# Install:
#  Copy trunk/boost/* to /usr/include/boost/ recursively then copy
#  trunk/boost/bloom_filter/detail/* to /usr/include/boost/detail/
# You also need the library for running the client, so libboost is needed.
#  sudo apt-get install libboost1.40-all-dev 
#
# This is tested for Ubuntu 10.04 and 10.10 (but with 1.42).

# Check which boards to use...
if [ $# == 0 ]; then
	FROM=1
	TO=136
elif [ $# == 1 ]; then
	FROM=1
	TO=$1
elif [ $# == 2 ]; then
	FROM=$1
	TO=$2
else
	echo "Wut?" 1>&2
	exit -1
fi

# ..., compile...
make

# ... and let the fun begin. :-)
for i in $(seq $FROM $TO); do
	./main $i
done

exit 0
