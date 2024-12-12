#!/bin/bash

source scripts/run_summary.sh ppt runlist/ppt/runlist_40Ca.txt
source scripts/run_summary.sh ppt runlist/ppt/runlist_42Ca.txt
source scripts/run_summary.sh ppt runlist/ppt/runlist_44Ca.txt
source scripts/run_summary.sh ppt runlist/ppt/runlist_48Ca.txt
source scripts/run_summary.sh ppt runlist/ppt/runlist_carbon.txt
source scripts/run_summary.sh ppt runlist/ppt/runlist_mylar.txt

wait
echo "run_summary.yaml for ppt : All tasks are completed. "
