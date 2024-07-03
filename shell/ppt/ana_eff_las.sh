#!/bin/bash

export LOG=shell/ppt/log

echo `date` > $LOG/eff_las_40Ca.log
echo `date` > $LOG/eff_las_42Ca.log
echo `date` > $LOG/eff_las_44Ca.log
echo `date` > $LOG/eff_las_48Ca.log
echo `date` > $LOG/eff_las_carbon.log
echo `date` > $LOG/eff_las_mylar.log

source shell/eff_las.sh ppt runlist/ppt/runlist_40Ca.txt >> $LOG/eff_las_40Ca.log &
source shell/eff_las.sh ppt runlist/ppt/runlist_42Ca.txt >> $LOG/eff_las_42Ca.log &
source shell/eff_las.sh ppt runlist/ppt/runlist_44Ca.txt >> $LOG/eff_las_44Ca.log & 
source shell/eff_las.sh ppt runlist/ppt/runlist_48Ca.txt >> $LOG/eff_las_48Ca.log & 
source shell/eff_las.sh ppt runlist/ppt/runlist_carbon.txt >> $LOG/eff_las_carbon.log &
source shell/eff_las.sh ppt runlist/ppt/runlist_mylar.txt >> $LOG/eff_las_mylar.log &

wait
echo "eff_las.yaml for ppt : All tasks are completed. "
