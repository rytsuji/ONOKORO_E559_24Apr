#!/bin/bash

source scripts/phys_nogate.sh pph runlist/pph/runlist_40Ca.txt 
source scripts/phys_nogate.sh pph runlist/pph/runlist_42Ca.txt 
source scripts/phys_nogate.sh pph runlist/pph/runlist_44Ca.txt 
source scripts/phys_nogate.sh pph runlist/pph/runlist_carbon.txt
source scripts/phys_nogate.sh pph runlist/pph/runlist_mylar.txt

wait
echo "phys_nogate.yaml for pph : All tasks are completed. "
