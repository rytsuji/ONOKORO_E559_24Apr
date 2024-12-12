#!/bin/bash

source scripts/run_summary.sh pph runlist/pph/runlist_40Ca.txt 
source scripts/run_summary.sh pph runlist/pph/runlist_42Ca.txt 
source scripts/run_summary.sh pph runlist/pph/runlist_44Ca.txt 
source scripts/run_summary.sh pph runlist/pph/runlist_carbon.txt
source scripts/run_summary.sh pph runlist/pph/runlist_mylar.txt

wait
echo "run_summary.yaml for pph : All tasks are completed. "
