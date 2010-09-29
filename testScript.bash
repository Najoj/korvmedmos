#!/bin/bash

# Run like  ./testScript.bash &> RUN  to make a new RUN file.
# Count number of good solutions with  grep -c Good RUN

# Compile...
make

# ... and let the fun begin. :-)
for i in $(seq 1 136); do
    echo -ne "=== $i ===\n"
    time ./main $i
    ps -e | grep main | awk '{print $3}'
    echo -e "\n"
done

# To make a process kill after given time use timelimit.bash
