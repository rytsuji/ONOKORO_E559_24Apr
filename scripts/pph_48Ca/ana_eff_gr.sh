#!/bin/bash

export LOG=scripts/pph_48Ca/log

echo `date` > $LOG/eff_gr_48Ca.log
echo `date` > $LOG/eff_gr_carbon.log
echo `date` > $LOG/eff_gr_mylar.log

source scripts/eff_gr.sh pph_48Ca runlist/pph_48Ca/runlist_48Ca.txt >> $LOG/eff_gr_48Ca.log & 
source scripts/eff_gr.sh pph_48Ca runlist/pph_48Ca/runlist_carbon.txt >> $LOG/eff_gr_carbon.log &
source scripts/eff_gr.sh pph_48Ca runlist/pph_48Ca/runlist_mylar.txt >> $LOG/eff_gr_mylar.log &

wait
echo "eff_gr.yaml for pph_48Ca : All tasks are completed. "
