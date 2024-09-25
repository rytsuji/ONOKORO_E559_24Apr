#!/bin/bash

#export MACRO=ppX_ang.C\(1\,0\,26.36\,610.965\,0.0\,\"dat/ppt_40Ca.dat\"\)

root -b -q ppX_ang.C\(1\,0\,26.36\,149\,\"dat/ppt_40Ca_center.gated.dat\"\) & 
root -b -q ppX_ang.C\(1\,0\,26.36\,153\,\"dat/ppt_40Ca_pos.gated.dat\"\) &
root -b -q ppX_ang.C\(1\,0\,26.36\,145\,\"dat/ppt_40Ca_neg.gated.dat\"\) &

root -b -q ppX_ang.C\(1\,4\,27.36\,151\,\"dat/ppt_12C_center.gated.dat\"\) & 
root -b -q ppX_ang.C\(1\,4\,27.36\,148\,\"dat/ppt_12C_pos.gated.dat\"\) &
root -b -q ppX_ang.C\(1\,4\,27.36\,145\,\"dat/ppt_12C_neg.gated.dat\"\)

root -b -q ppX_ang.C\(1\,4\,27.36\,145\,\"dat/ppt_12C.gated1.dat\"\) &
root -b -q ppX_ang.C\(1\,4\,27.36\,146.5\,\"dat/ppt_12C.gated2.dat\"\) &
root -b -q ppX_ang.C\(1\,4\,27.36\,148\,\"dat/ppt_12C.gated3.dat\"\) &
root -b -q ppX_ang.C\(1\,4\,27.36\,149.5\,\"dat/ppt_12C.gated4.dat\"\) &
root -b -q ppX_ang.C\(1\,4\,27.36\,151\,\"dat/ppt_12C.gated5.dat\"\) & 

