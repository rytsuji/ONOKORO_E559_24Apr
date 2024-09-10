{
  TCut pid_gr="pid_gr.fCharge>0 && abs(fmod(pid_gr.fTiming-pgr.GetTOF()-rf2.fTiming+1420.675,142.0675/2.0)-45.55)<2.5";
  TCut pid_las="abs(pid_las.fCharge-150)<50 && abs(fmod(pid_las.fTiming-plas.GetTOF()-rf1.fTiming+1420.675,142.0675/2.0)-40)<10";
  TCut tc="abs(tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))<20";

  TCut alas="abs(ltgt.fA*1000)<50 && abs(ltgt.fB*1000)<60";
  TCut agr="abs(gtgt.fA*1000)<15 && abs(gtgt.fB*1000)<30 && (gtgt.fDelta)<0.175";

  tree->SetAlias("TOF","tof.fTiming-(pgr.GetTOF()-plas.GetTOF())");

  tree->SetAlias("TOF","tof.fTiming");
}
