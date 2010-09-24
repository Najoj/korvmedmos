#!/bin/sh

# You need boost bloom filter to run this program.
# Get code:
#  svn co https://svn.boost.org/svn/boost/sandbox/bloom_filter/trunk/
# Install:
#  Go to trunk/boost/ and copy * to /usr/include/boost/ (recursively) then copy
#  trunk/boost/bloom_filter/detail/* to /usr/include/boost/detail

# Compile...
make

# ... and let the fun begin. :-)
for i in $(seq 1 136); do
    ./main $i
done
