#!/bin/bash

export LOG=scripts/ppt/log

echo `date` > $LOG/calib_pid_40Ca.log
echo `date` > $LOG/calib_pid_42Ca.log
echo `date` > $LOG/calib_pid_44Ca.log
echo `date` > $LOG/calib_pid_48Ca.log
echo `date` > $LOG/calib_pid_carbon.log
echo `date` > $LOG/calib_pid_mylar.log

source scripts/calib_pid.sh ppt runlist/ppt/runlist_40Ca.txt >> $LOG/calib_pid_40Ca.log &
source scripts/calib_pid.sh ppt runlist/ppt/runlist_42Ca.txt >> $LOG/calib_pid_42Ca.log &
source scripts/calib_pid.sh ppt runlist/ppt/runlist_44Ca.txt >> $LOG/calib_pid_44Ca.log & 
source scripts/calib_pid.sh ppt runlist/ppt/runlist_48Ca.txt >> $LOG/calib_pid_48Ca.log & 
source scripts/calib_pid.sh ppt runlist/ppt/runlist_carbon.txt >> $LOG/calib_pid_carbon.log &
source scripts/calib_pid.sh ppt runlist/ppt/runlist_mylar.txt >> $LOG/calib_pid_mylar.log &

wait
echo "calib_pid.yaml for ppt : All tasks are completed. "
