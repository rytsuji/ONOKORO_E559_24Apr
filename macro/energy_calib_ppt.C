{
  tree->SetAlias("Tgr","sqrt( pow(938.7,2.0) + pow( 0.3*3.0*610.965*(1+gtgt.fDelta) , 2.0) )-938.7");
  tree->SetAlias("Tlas","sqrt( pow(2808.92, 2.0) + pow( 0.3*1.75*1.0*1052.305*(1+ltgt.fDelta) , 2.0) )-2808.92");

  tree->SetAlias("Sx","226.0-Tgr-Tlas");
  tree->SetAlias("tof","pid_gr.fTiming-pid_las.fTiming");
  //tree->SetAlias("tof","tref_las.fTiming-tref_grtrig.fTiming");

  TCut pid_gr="pid_gr.fCharge < 1000 && abs( fmod(pla_gr_1.fTiming-rf2.fTiming+1420.6750,71.033750)-37.5)<17.5";
  TCut pid_las="pid_las.fCharge>100 && abs( fmod(pla_las_3.fTiming-rf2.fTiming+1420.6750,71.033750)-55)<15";
  TCut tc="abs(tof+1155)<30"
  
}
