#!/Bin/bash

export LOG=scripts/pph_48Ca/log

echo `date` > $LOG/eff_las_48Ca.log
echo `date` > $LOG/eff_las_carbon.log
echo `date` > $LOG/eff_las_mylar.log

source scripts/eff_las.sh pph_48Ca runlist/pph_48Ca/runlist_48Ca.txt >> $LOG/eff_las_48Ca.log & 
source scripts/eff_las.sh pph_48Ca runlist/pph_48Ca/runlist_carbon.txt >> $LOG/eff_las_carbon.log &
source scripts/eff_las.sh pph_48Ca runlist/pph_48Ca/runlist_mylar.txt >> $LOG/eff_las_mylar.log &

wait
echo "eff_las.yaml for pph_48Ca : All tasks are completed. "
