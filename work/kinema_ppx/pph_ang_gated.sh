#!/bin/bash

#export MACRO=ppX_ang.C\(1\,0\,26.36\,610.965\,0.0\,\"dat/ppt_40Ca.dat\"\)

root -b -q ppX_ang.C\(2\,0\,20.23\,149\,\"dat/pph_40Ca_center.gated.dat\"\) & 
root -b -q ppX_ang.C\(2\,0\,20.23\,153\,\"dat/pph_40Ca_pos.gated.dat\"\) &
root -b -q ppX_ang.C\(2\,0\,20.23\,145\,\"dat/pph_40Ca_neg.gated.dat\"\)

#root -b -q ppX_ang.C\(2\,4\,26.28\,153\,\"dat/pph_12C_center.gated.dat\"\) & 
#root -b -q ppX_ang.C\(2\,4\,26.28\,149.5\,\"dat/pph_12C_pos.gated.dat\"\) &
#root -b -q ppX_ang.C\(2\,4\,26.28\,146\,\"dat/pph_12C_neg.gated.dat\"\)

root -b -q ppX_ang.C\(2\,4\,26.28\,152\,\"dat/pph_12C_center.gated.dat\"\) & 
root -b -q ppX_ang.C\(2\,4\,26.28\,149\,\"dat/pph_12C_pos.gated.dat\"\) &
root -b -q ppX_ang.C\(2\,4\,26.28\,146\,\"dat/pph_12C_neg.gated.dat\"\)

root -b -q ppX_ang.C\(2\,4\,26.28\,146\,\"dat/pph_12C.gated1.dat\"\) &
root -b -q ppX_ang.C\(2\,4\,26.28\,147.5\,\"dat/pph_12C.gated2.dat\"\) &
root -b -q ppX_ang.C\(2\,4\,26.28\,149\,\"dat/pph_12C.gated3.dat\"\) &
root -b -q ppX_ang.C\(2\,4\,26.28\,150.5\,\"dat/pph_12C.gated4.dat\"\) &
root -b -q ppX_ang.C\(2\,4\,26.28\,152\,\"dat/pph_12C.gated5.dat\"\) & 




