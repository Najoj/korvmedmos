#!/bin/bash

# Run like  ./testScript.bash &> RUN  to make a new RUNX file.
# Count number of good solutions with  grep -c Good RUNX

# Compile...
make

./timelimit.bash &
sleep 2

# ... and let the fun begin. :-)
for i in $(seq 1 136); do
    echo -ne "=== $i ===\n"
#    time ./main $i
    time ./server.bash nya_banor $i | ./main
    echo -e "\n"
    sleep 2
done

killall -9 timelimit.bash