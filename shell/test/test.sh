#!/bin/bash
export LOG=shell/test/test.log
 
source shell/rawdata.sh ppt shell/test/test1.txt >> $LOG &
source shell/rawdata.sh ppt shell/test/test2.txt >> $LOG &

wait
echo "rawdata.yaml test : All tasks are completed. "
