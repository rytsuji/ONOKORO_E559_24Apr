{
  tree->SetAlias("Tgr","sqrt( pow(938.7,2.0) + pow( 0.3*3.0*635.358*(1+gtgt.fDelta) , 2.0) )-938.7");
  tree->SetAlias("Tlas","sqrt( pow(2808.92, 2.0) + pow( 0.3*1.75*1.0*1071.412*(1+ltgt.fDelta) , 2.0) )-2808.92");
  tree->SetAlias("Sx","226.0-Tgr-Tlas");
  tree->SetAlias("tof","pid_gr.fTiming-pid_las.fTiming");
  TCut pid_gr="pid_gr.fCharge >0 && abs( fmod(pid_gr.fTiming-rf2.fTiming+1420.6750,71.033750)-35)<20";
  TCut pid_las="pid_las.fCharge>100 && abs( fmod(pid_las.fTiming-rf3.fTiming+1420.6750,71.033750)-30)<20";
  TCut tc="abs(tof+1150)<30";
}
