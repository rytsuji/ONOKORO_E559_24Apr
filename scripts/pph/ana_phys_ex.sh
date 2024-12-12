#!/bin/bash 


source scripts/phys_ex.sh pph 40Ca runlist/pph/runlist_40Ca.txt &
source scripts/phys_ex.sh pph 42Ca runlist/pph/runlist_42Ca.txt &
source scripts/phys_ex.sh pph 44Ca runlist/pph/runlist_44Ca.txt &
source scripts/phys_ex.sh pph 40Ca runlist/pph/runlist_carbon.txt &
source scripts/phys_ex.sh pph 40Ca runlist/pph/runlist_mylar.txt &
source scripts/phys_ex.sh pph 42Ca runlist/pph/runlist_carbon.txt &
source scripts/phys_ex.sh pph 42Ca runlist/pph/runlist_mylar.txt &
source scripts/phys_ex.sh pph 44Ca runlist/pph/runlist_carbon.txt &
source scripts/phys_ex.sh pph 44Ca runlist/pph/runlist_mylar.txt &


wait
echo "phys_ex.yaml for pph : All tasks are completed. "
