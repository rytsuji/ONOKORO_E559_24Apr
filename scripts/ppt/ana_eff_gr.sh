#!/bin/bash

export LOG=scripts/ppt/log

echo `date` > $LOG/eff_gr_40Ca.log
echo `date` > $LOG/eff_gr_42Ca.log
echo `date` > $LOG/eff_gr_44Ca.log
echo `date` > $LOG/eff_gr_48Ca.log
echo `date` > $LOG/eff_gr_carbon.log
echo `date` > $LOG/eff_gr_mylar.log

source scripts/eff_gr.sh ppt runlist/ppt/runlist_40Ca.txt >> $LOG/eff_gr_40Ca.log &
source scripts/eff_gr.sh ppt runlist/ppt/runlist_42Ca.txt >> $LOG/eff_gr_42Ca.log &
source scripts/eff_gr.sh ppt runlist/ppt/runlist_44Ca.txt >> $LOG/eff_gr_44Ca.log & 
source scripts/eff_gr.sh ppt runlist/ppt/runlist_48Ca.txt >> $LOG/eff_gr_48Ca.log & 
source scripts/eff_gr.sh ppt runlist/ppt/runlist_carbon.txt >> $LOG/eff_gr_carbon.log &
source scripts/eff_gr.sh ppt runlist/ppt/runlist_mylar.txt >> $LOG/eff_gr_mylar.log &

wait
echo "eff_gr.yaml for ppt : All tasks are completed. "
