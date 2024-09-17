#!/bin/bash 

export LOG=scripts/ppt/log

echo `date` > $LOG/phys_40Ca.log
echo `date` > $LOG/phys_42Ca.log
echo `date` > $LOG/phys_44Ca.log
echo `date` > $LOG/phys_48Ca.log
echo `date` > $LOG/phys_carbon.log
echo `date` > $LOG/phys_mylar.log

#source scripts/phys.sh ppt runlist/ppt/runlist_40Ca.txt >> $LOG/phys_40Ca.log &
source scripts/phys_momentum.sh ppt 40Ca runlist/ppt/runlist_40Ca.txt >> $LOG/phys_40Ca.log &
source scripts/phys.sh ppt runlist/ppt/runlist_42Ca.txt >> $LOG/phys_42Ca.log &
source scripts/phys.sh ppt runlist/ppt/runlist_44Ca.txt >> $LOG/phys_44Ca.log & 
source scripts/phys.sh ppt runlist/ppt/runlist_48Ca.txt >> $LOG/phys_48Ca.log & 
#source scripts/phys.sh ppt runlist/ppt/runlist_carbon.txt >> $LOG/phys_carbon.log &
source scripts/phys_momentum.sh ppt carbon runlist/ppt/runlist_carbon.txt >> $LOG/phys_carbon.log &
source scripts/phys.sh ppt runlist/ppt/runlist_mylar.txt >> $LOG/phys_mylar.log &

wait
echo "phys.yaml for ppt : All tasks are completed. "
