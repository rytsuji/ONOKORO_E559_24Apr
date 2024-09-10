#!/bin/bash

export LOG=scripts/ppt/log

echo `date` > $LOG/calib_40Ca.log
echo `date` > $LOG/calib_42Ca.log
echo `date` > $LOG/calib_44Ca.log
echo `date` > $LOG/calib_48Ca.log
#echo `date` > $LOG/calib_carbon.log
echo `date` > $LOG/calib_mylar.log

source scripts/calib.sh ppt runlist/ppt/runlist_40Ca.txt >> $LOG/calib_40Ca.log &
source scripts/calib.sh ppt runlist/ppt/runlist_42Ca.txt >> $LOG/calib_42Ca.log &
source scripts/calib.sh ppt runlist/ppt/runlist_44Ca.txt >> $LOG/calib_44Ca.log & 
source scripts/calib.sh ppt runlist/ppt/runlist_48Ca.txt >> $LOG/calib_48Ca.log & 
#source scripts/calib.sh ppt runlist/ppt/runlist_carbon.txt >> $LOG/calib_carbon.log &
source scripts/calib.sh ppt runlist/ppt/runlist_mylar.txt >> $LOG/calib_mylar.log &

wait
echo "calib.yaml for ppt : All tasks are completed. "
