#!/bin/bash

export LOG=scripts/pph_48Ca/log

echo `date` > $LOG/rawdata_48Ca.log
echo `date` > $LOG/rawdata_carbon.log
echo `date` > $LOG/rawdata_mylar.log

source scripts/rawdata.sh pph_48Ca runlist/pph_48Ca/runlist_48Ca.txt >> $LOG/rawdata_48Ca.log & 
source scripts/rawdata.sh pph_48Ca runlist/pph_48Ca/runlist_carbon.txt >> $LOG/rawdata_carbon.log &
source scripts/rawdata.sh pph_48Ca runlist/pph_48Ca/runlist_mylar.txt >> $LOG/rawdata_mylar.log &

wait
echo "rawdata.yaml for pph_48Ca : All tasks are completed. "
