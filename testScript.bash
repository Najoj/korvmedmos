#!/bin/bash

# Run like  ./testScript.bash &> RUN  to make a new RUN file.
# Count number of good solutions with  grep -c Good RUN

# Compile...
make

# ... and let the fun begin. :-)
for i in $(seq 1 136); do
    echo -ne "$i:\t"
    time ./main $i
    echo -e "\n"
done
