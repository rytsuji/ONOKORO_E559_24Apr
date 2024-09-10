#!/bin/bash

FILE_NAME=$3
while read LINE
do
    export MACRO=scripts/phys_momentum.C\($LINE\,\"$1\"\,\"$2\"\)
    echo $MACRO    
    a -b -q $MACRO $    
    wait

done < ${FILE_NAME}



wait
