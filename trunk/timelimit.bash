#!/bin/bash

# Limit time time usage for main.

# Use "HH:MM:SS" format.
LIMIT="00:01:00"

while true; do
    if [ "$(ps -e | grep main | awk '{print $3}')" == $LIMIT ]; then
        killall -9 main
    fi
    # Should we sleep here?
done
