#!/Bin/bash
export LOG=shell/pph/log

echo `date` > $LOG/eff_gr_40Ca.log
echo `date` > $LOG/eff_gr_42Ca.log
echo `date` > $LOG/eff_gr_44Ca.log
echo `date` > $LOG/eff_gr_carbon.log
echo `date` > $LOG/eff_gr_mylar.log

source shell/eff_gr.sh pph runlist/pph/runlist_40Ca.txt >> $LOG/eff_gr_40Ca.log &
source shell/eff_gr.sh pph runlist/pph/runlist_42Ca.txt >> $LOG/eff_gr_42Ca.log &
source shell/eff_gr.sh pph runlist/pph/runlist_44Ca.txt >> $LOG/eff_gr_44Ca.log & 
source shell/eff_gr.sh pph runlist/pph/runlist_carbon.txt >> $LOG/eff_gr_carbon.log &
source shell/eff_gr.sh pph runlist/pph/runlist_mylar.txt >> $LOG/eff_gr_mylar.log &

wait
echo "eff_gr.yaml for pph : All tasks are completed. "
