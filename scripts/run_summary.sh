#!/bin/bash

FILE_NAME=$2
while read LINE
do
    export MACRO=scripts/run_summary.C\($LINE\,\"$1\"\)
    a -b -q $MACRO $
    wait
    
done < ${FILE_NAME}



wait
