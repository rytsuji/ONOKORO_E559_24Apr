{
  tree->SetAlias("Tgr","sqrt( pow(938.7,2.0) + pow( 0.3*3.0*610.965*(1+gtgt.fDelta) , 2.0) )-938.7");
  tree->SetAlias("Tlas","sqrt( pow(2808.92, 2.0) + pow( 0.3*1.75*1.0*1052.305*(1+ltgt.fDelta) , 2.0) )-2808.92");
  tree->SetAlias("Sx","226.0-Tgr-Tlas");
  //tree->SetAlias("tof","pid_gr.fTiming-pid_las.fTiming");
  tree->SetAlias("tof","tref_las.fTiming-tref_grtrig.fTiming");
  TCut pid_gr="abs(pla_gr_1.fCharge -550)<450 && abs( fmod(tref_grtrig.fTiming-rf2.fTiming+1420.6750,71.033750)-47.5)<17.5";
  TCut pid_las="pid_las.fCharge>100 && abs( fmod(tref_las.fTiming-rf1.fTiming+1420.6750,71.033750)-35)<15";
  TCut tc="tof>650 && tof<720"
  
}
