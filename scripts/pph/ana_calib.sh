
#!/bin/bash
export LOG=scripts/pph/log

echo `date` > $LOG/calib_40Ca.log
echo `date` > $LOG/calib_42Ca.log
echo `date` > $LOG/calib_44Ca.log
echo `date` > $LOG/calib_carbon.log
echo `date` > $LOG/calib_mylar.log

source scripts/calib.sh pph runlist/pph/runlist_40Ca.txt >> $LOG/calib_40Ca.log &
source scripts/calib.sh pph runlist/pph/runlist_42Ca.txt >> $LOG/calib_42Ca.log &
source scripts/calib.sh pph runlist/pph/runlist_44Ca.txt >> $LOG/calib_44Ca.log & 
source scripts/calib.sh pph runlist/pph/runlist_carbon.txt >> $LOG/calib_carbon.log &
source scripts/calib.sh pph runlist/pph/runlist_mylar.txt >> $LOG/calib_mylar.log &

wait
echo "calib.yaml for pph : All tasks are completed. "
