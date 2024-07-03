#!/bin/bash
export LOG=shell/pph/log

echo `date` > $LOG/eff_las_40Ca.log
echo `date` > $LOG/eff_las_42Ca.log
echo `date` > $LOG/eff_las_44Ca.log
echo `date` > $LOG/eff_las_carbon.log
echo `date` > $LOG/eff_las_mylar.log

source shell/eff_las.sh pph runlist/pph/runlist_40Ca.txt >> $LOG/eff_las_40Ca.log &
source shell/eff_las.sh pph runlist/pph/runlist_42Ca.txt >> $LOG/eff_las_42Ca.log &
source shell/eff_las.sh pph runlist/pph/runlist_44Ca.txt >> $LOG/eff_las_44Ca.log & 
source shell/eff_las.sh pph runlist/pph/runlist_carbon.txt >> $LOG/eff_las_carbon.log &
source shell/eff_las.sh pph runlist/pph/runlist_mylar.txt >> $LOG/eff_las_mylar.log &

wait
echo "eff_las.yaml for pph : All tasks are completed. "
