#!/bin/bash

#export MACRO=ppX_ang.C\(1\,0\,26.36\,610.965\,0.0\,\"dat/ppt_40Ca.dat\"\)

root -b -q ppX_ang.C\(2\,0\,20.23\,149\,\"dat/pph_40Ca_center.dat\"\) & 
root -b -q ppX_ang.C\(2\,0\,20.23\,153\,\"dat/pph_40Ca_pos.dat\"\) &
root -b -q ppX_ang.C\(2\,0\,20.23\,145\,\"dat/pph_40Ca_neg.dat\"\)


root -b -q ppX_ang.C\(2\,1\,22.58\,149\,\"dat/pph_42Ca_center.dat\"\) & 
root -b -q ppX_ang.C\(2\,1\,22.58\,152\,\"dat/pph_42Ca_pos.dat\"\) &
root -b -q ppX_ang.C\(2\,1\,22.58\,145\,\"dat/pph_42Ca_neg.dat\"\)


root -b -q ppX_ang.C\(2\,2\,25.19\,149\,\"dat/pph_44Ca_center.dat\"\) & 
root -b -q ppX_ang.C\(2\,2\,25.19\,152\,\"dat/pph_44Ca_pos.dat\"\) &
root -b -q ppX_ang.C\(2\,2\,25.19\,145\,\"dat/pph_44Ca_neg.dat\"\)


root -b -q ppX_ang.C\(2\,4\,26.28\,149\,\"dat/pph_12C_center.dat\"\) & 
root -b -q ppX_ang.C\(2\,4\,26.28\,152\,\"dat/pph_12C_pos.dat\"\) &
root -b -q ppX_ang.C\(2\,4\,26.28\,145\,\"dat/pph_12C_neg.dat\"\)

root -b -q ppX_ang.C\(2\,3\,31.80\,141\,\"dat/pph_48Ca_center.dat\"\) & 
root -b -q ppX_ang.C\(2\,3\,31.80\,146\,\"dat/pph_48Ca_pos.dat\"\) &
root -b -q ppX_ang.C\(2\,3\,31.80\,136\,\"dat/pph_48Ca_neg.dat\"\)


