#!/bin/bash

FILE_NAME=$2
while read LINE
do
    export MACRO=scripts/calib_pid.C\($LINE\,\"$1\"\)
    a -b -q $MACRO $
    wait
    
done < ${FILE_NAME}



wait
