#!/bin/bash 

source scripts/phys_ex.sh pph_48Ca 48Ca runlist/pph_48Ca/runlist_48Ca.txt &
source scripts/phys_ex.sh pph_48Ca 48Ca runlist/pph_48Ca/runlist_carbon.txt &
source scripts/phys_ex.sh pph_48Ca 48Ca runlist/pph_48Ca/runlist_mylar.txt &

wait
echo "phys_ex.yaml for pph_48Ca : All tasks are completed. "
