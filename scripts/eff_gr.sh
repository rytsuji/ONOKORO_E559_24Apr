#!/bin/bash

FILE_NAME=$2
while read LINE
do
    export MACRO=scripts/eff_gr.C\($LINE\,\"$1\"\)
    echo $MACRO    
    a -b -q $MACRO $    
    wait

done < ${FILE_NAME}



wait
