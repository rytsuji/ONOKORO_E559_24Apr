#!/bin/bash
export LOG=scripts/pph/log

echo `date` > $LOG/rawdata_40Ca.log
echo `date` > $LOG/rawdata_42Ca.log
echo `date` > $LOG/rawdata_44Ca.log
echo `date` > $LOG/rawdata_carbon.log
echo `date` > $LOG/rawdata_mylar.log

source scripts/rawdata.sh pph runlist/pph/runlist_40Ca.txt >> $LOG/rawdata_40Ca.log &
source scripts/rawdata.sh pph runlist/pph/runlist_42Ca.txt >> $LOG/rawdata_42Ca.log &
source scripts/rawdata.sh pph runlist/pph/runlist_44Ca.txt >> $LOG/rawdata_44Ca.log & 
source scripts/rawdata.sh pph runlist/pph/runlist_carbon.txt >> $LOG/rawdata_carbon.log &
source scripts/rawdata.sh pph runlist/pph/runlist_mylar.txt >> $LOG/rawdata_mylar.log &

wait
echo "rawdata.yaml for pph : All tasks are completed. "
