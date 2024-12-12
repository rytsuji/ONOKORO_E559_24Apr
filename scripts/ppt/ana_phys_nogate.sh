#!/bin/bash 

#export LOG=scripts/ppt/log

#echo `date` > $LOG/phys_40Ca.log
#echo `date` > $LOG/phys_42Ca.log
#echo `date` > $LOG/phys_44Ca.log
#echo `date` > $LOG/phys_48Ca.log
#echo `date` > $LOG/phys_carbon.log
#echo `date` > $LOG/phys_mylar.log

source scripts/phys_nogate.sh ppt runlist/ppt/runlist_40Ca.txt 


wait
echo "phys.yaml for ppt : All tasks are completed. "
