#!/bin/bash
export LOG=scripts/pph/log

echo `date` > $LOG/phys_40Ca.log
echo `date` > $LOG/phys_42Ca.log
echo `date` > $LOG/phys_44Ca.log
echo `date` > $LOG/phys_carbon.log
echo `date` > $LOG/phys_mylar.log

source scripts/phys.sh pph runlist/pph/runlist_40Ca.txt >> $LOG/phys_40Ca.log &
#source scripts/phys_momentum.sh pph 40Ca runlist/pph/runlist_40Ca.txt >> $LOG/phys_40Ca.log &
source scripts/phys.sh pph runlist/pph/runlist_42Ca.txt >> $LOG/phys_42Ca.log & 
source scripts/phys.sh pph runlist/pph/runlist_44Ca.txt >> $LOG/phys_44Ca.log & 
source scripts/phys.sh pph runlist/pph/runlist_carbon.txt >> $LOG/phys_carbon.log &
#source scripts/phys_momentum.sh pph carbon runlist/pph/runlist_carbon.txt >> $LOG/phys_carbon.log &
source scripts/phys.sh pph runlist/pph/runlist_mylar.txt >> $LOG/phys_mylar.log &

wait
echo "phys.yaml for pph : All tasks are completed. "
