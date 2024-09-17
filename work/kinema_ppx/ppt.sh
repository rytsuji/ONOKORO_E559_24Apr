#!/bin/bash
export MACRO=ppX.C\(1\,0\,26.36\,0.0\,51.23\,50.89\,610.965\,\"root/ppt_40Ca_kf0.root\"\)
#export MACRO=ppX.C\(1\,0\,26.36\,200.0\,51.23\,50.89\,610.965\,\"ppt_40Ca_kf200.root\"\)
root -b -q $MACRO 
