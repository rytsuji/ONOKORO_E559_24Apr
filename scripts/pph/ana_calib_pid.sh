
#!/bin/bash
export LOG=scripts/pph/log

echo `date` > $LOG/calib_pid_40Ca.log
echo `date` > $LOG/calib_pid_42Ca.log
echo `date` > $LOG/calib_pid_44Ca.log
echo `date` > $LOG/calib_pid_carbon.log
echo `date` > $LOG/calib_pid_mylar.log

source scripts/calib_pid.sh pph runlist/pph/runlist_40Ca.txt >> $LOG/calib_pid_40Ca.log &
source scripts/calib_pid.sh pph runlist/pph/runlist_42Ca.txt >> $LOG/calib_pid_42Ca.log &
source scripts/calib_pid.sh pph runlist/pph/runlist_44Ca.txt >> $LOG/calib_pid_44Ca.log & 
source scripts/calib_pid.sh pph runlist/pph/runlist_carbon.txt >> $LOG/calib_pid_carbon.log &
source scripts/calib_pid.sh pph runlist/pph/runlist_mylar.txt >> $LOG/calib_pid_mylar.log &

wait
echo "calib_pid.yaml for pph : All tasks are completed. "
