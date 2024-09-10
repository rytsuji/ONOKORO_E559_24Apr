#!/bin/bash
export LOG=scripts/ppt/log

echo `date` > $LOG/rawdata_40Ca.log
echo `date` > $LOG/rawdata_42Ca.log
echo `date` > $LOG/rawdata_44Ca.log
echo `date` > $LOG/rawdata_48Ca.log
echo `date` > $LOG/rawdata_carbon.log
echo `date` > $LOG/rawdata_mylar.log
 
source scripts/rawdata.sh ppt runlist/ppt/runlist_40Ca.txt >> $LOG/rawdata_40Ca.log &
source scripts/rawdata.sh ppt runlist/ppt/runlist_42Ca.txt >> $LOG/rawdata_42Ca.log &
source scripts/rawdata.sh ppt runlist/ppt/runlist_44Ca.txt >> $LOG/rawdata_44Ca.log & 
source scripts/rawdata.sh ppt runlist/ppt/runlist_48Ca.txt >> $LOG/rawdata_48Ca.log & 
source scripts/rawdata.sh ppt runlist/ppt/runlist_carbon.txt >> $LOG/rawdata_carbon.log &
source scripts/rawdata.sh ppt runlist/ppt/runlist_mylar.txt >> $LOG/rawdata_mylar.log &

wait
echo "rawdata.yaml for ppt : All tasks are completed. "
