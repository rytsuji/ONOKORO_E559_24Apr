#!/bin/bash

export LOG=scripts/pph_48Ca/log

echo `date` > $LOG/calib_48Ca.log
echo `date` > $LOG/calib_carbon.log
echo `date` > $LOG/calib_mylar.log

source scripts/calib.sh pph_48Ca runlist/pph_48Ca/runlist_48Ca.txt >> $LOG/calib_48Ca.log & 
source scripts/calib.sh pph_48Ca runlist/pph_48Ca/runlist_carbon.txt >> $LOG/calib_carbon.log &
source scripts/calib.sh pph_48Ca runlist/pph_48Ca/runlist_mylar.txt >> $LOG/calib_mylar.log &

wait
echo "calib.yaml for pph_48Ca : All tasks are completed. "
