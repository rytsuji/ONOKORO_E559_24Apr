#!/bin/bash

export LOG=scripts/pph_48Ca/log

echo `date` > $LOG/calib_pid_48Ca.log
echo `date` > $LOG/calib_pid_carbon.log
echo `date` > $LOG/calib_pid_mylar.log

source scripts/calib_pid.sh pph_48Ca runlist/pph_48Ca/runlist_48Ca.txt >> $LOG/calib_pid_48Ca.log & 
source scripts/calib_pid.sh pph_48Ca runlist/pph_48Ca/runlist_carbon.txt >> $LOG/calib_pid_carbon.log &
source scripts/calib_pid.sh pph_48Ca runlist/pph_48Ca/runlist_mylar.txt >> $LOG/calib_pid_mylar.log &

wait
echo "calib_pid.yaml for pph_48Ca : All tasks are completed. "
