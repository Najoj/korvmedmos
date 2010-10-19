#!/bin/bash

# Run like  ./testScript.bash

# Compile...
make

# Start the timelimit script.
./timelimit.bash &
sleep 2

# ... and let the fun begin. :-)
for i in $(seq 1 136); do
    echo -ne "=== $i ===\n"
    # Prints time to stdout aswell.
    (time ./sokoban $i) 2>&1
    echo -e "\n"
    sleep 2
done

killall -9 timelimit.bash
