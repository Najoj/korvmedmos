#!/bin/bash

# Run like  ./testScript.bash &> RUN  to make a new RUN file.
# Count number of good solutions with  grep -c Good RUN

# Compile...
make

# ... and let the fun begin. :-)
for i in $(seq 1 136); do
    echo -ne "=== $i ===\n"
#    time ./main $i &
    time ./server.bash $i | ./main &
    sleep 1m 30s && killall -9 main
    echo -e "\n"
done
