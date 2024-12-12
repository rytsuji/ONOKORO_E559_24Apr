#!/bin/bash 


source scripts/phys_ex.sh ppt 40Ca runlist/ppt/runlist_40Ca.txt &
source scripts/phys_ex.sh ppt 42Ca runlist/ppt/runlist_42Ca.txt &
source scripts/phys_ex.sh ppt 44Ca runlist/ppt/runlist_44Ca.txt &
source scripts/phys_ex.sh ppt 48Ca runlist/ppt/runlist_48Ca.txt &
source scripts/phys_ex.sh ppt 40Ca runlist/ppt/runlist_carbon.txt &
source scripts/phys_ex.sh ppt 40Ca runlist/ppt/runlist_mylar.txt &
source scripts/phys_ex.sh ppt 42Ca runlist/ppt/runlist_carbon.txt &
source scripts/phys_ex.sh ppt 42Ca runlist/ppt/runlist_mylar.txt &
source scripts/phys_ex.sh ppt 44Ca runlist/ppt/runlist_carbon.txt &
source scripts/phys_ex.sh ppt 44Ca runlist/ppt/runlist_mylar.txt &
source scripts/phys_ex.sh ppt 48Ca runlist/ppt/runlist_carbon.txt &
source scripts/phys_ex.sh ppt 48Ca runlist/ppt/runlist_mylar.txt &

wait
echo "phys_ex.yaml for ppt : All tasks are completed. "
