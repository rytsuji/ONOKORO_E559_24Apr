#!/bin/bash

export LOG=scripts/pph_48Ca/log

echo `date` > $LOG/phys_48Ca.log
echo `date` > $LOG/phys_carbon.log
echo `date` > $LOG/phys_mylar.log

source scripts/phys.sh pph_48Ca runlist/pph_48Ca/runlist_48Ca.txt >> $LOG/phys_48Ca.log & 
source scripts/phys.sh pph_48Ca runlist/pph_48Ca/runlist_carbon.txt >> $LOG/phys_carbon.log &
source scripts/phys.sh pph_48Ca runlist/pph_48Ca/runlist_mylar.txt >> $LOG/phys_mylar.log &

wait
echo "phys.yaml for pph_48Ca : All tasks are completed. "
