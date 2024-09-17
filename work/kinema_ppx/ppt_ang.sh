#!/bin/bash

#export MACRO=ppX_ang.C\(1\,0\,26.36\,610.965\,0.0\,\"dat/ppt_40Ca.dat\"\)

root -b -q ppX_ang.C\(1\,0\,26.36\,149\,\"dat/ppt_40Ca_center.dat\"\) & 
root -b -q ppX_ang.C\(1\,0\,26.36\,153\,\"dat/ppt_40Ca_pos.dat\"\) &
root -b -q ppX_ang.C\(1\,0\,26.36\,145\,\"dat/ppt_40Ca_neg.dat\"\) &

root -b -q ppX_ang.C\(1\,1\,22.21\,149\,\"dat/ppt_42Ca_center.dat\"\) & 
root -b -q ppX_ang.C\(1\,1\,22.21\,153\,\"dat/ppt_42Ca_pos.dat\"\) &
root -b -q ppX_ang.C\(1\,1\,22.21\,145\,\"dat/ppt_42Ca_neg.dat\"\) &


root -b -q ppX_ang.C\(1\,2\,21.84\,149\,\"dat/ppt_44Ca_center.dat\"\) & 
root -b -q ppX_ang.C\(1\,2\,21.84\,153\,\"dat/ppt_44Ca_pos.dat\"\) &
root -b -q ppX_ang.C\(1\,2\,21.84\,145\,\"dat/ppt_44Ca_neg.dat\"\) &


root -b -q ppX_ang.C\(1\,3\,23.06\,149\,\"dat/ppt_48Ca_center.dat\"\) & 
root -b -q ppX_ang.C\(1\,3\,23.06\,153\,\"dat/ppt_48Ca_pos.dat\"\) &
root -b -q ppX_ang.C\(1\,3\,23.06\,145\,\"dat/ppt_48Ca_neg.dat\"\) &


root -b -q ppX_ang.C\(1\,4\,27.36\,149\,\"dat/ppt_12C_center.dat\"\) & 
root -b -q ppX_ang.C\(1\,4\,27.36\,153\,\"dat/ppt_12C_pos.dat\"\) &
root -b -q ppX_ang.C\(1\,4\,27.36\,145\,\"dat/ppt_12C_neg.dat\"\) 

