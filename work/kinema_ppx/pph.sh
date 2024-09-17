#!/bin/bash
export MACRO=ppX.C\(2\,0\,20.23\,0.0\,51.23\,50.89\,610.943\,\"root/pph_40Ca_kf0.root\"\)

export MACRO=ppX.C\(2\,0\,20.23\,200.0\,51.23\,50.89\,610.943\,\"root/pph_40Ca_kf200.root\"\)
#export MACRO=ppX.C\(2\,0\,20.23\,50.0\,51.23\,50.89\,610.943\,\"pph_40Ca_kf50.root\"\)
root -b -q $MACRO 
