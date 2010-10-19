#!/bin/bash

# Limit time time usage for main.

# Use "HH:MM" format.
LIMIT="00:01:"

echo "timelimit.bash: START"

while true; do
    if [ "$(ps -e | grep sokoban | grep $LIMIT)" != "" ]; then
        echo -n "timelimit.bash: POW! "
        killall -9 sokoban
        echo "HEADSHOT!"
        sleep 1
    fi
    # Should we sleep here?
    sleep 10
done
