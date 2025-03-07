{
  TCut agr="abs(pgr.GetTheta()-51.2)<1.0 && abs(pgr.GetPhi())<3.5 && abs(pgr.GetPhi())<(4.0*pgr.GetTheta()-199.3) && abs(pgr.GetPhi())<(-5.0*pgr.GetTheta()+262.5)";
  TCut alas="abs(plas.GetTheta()-50.9)<3.4 && abs(fmod(plas.GetPhi()+360.0,360.0)-180)<4";
  TCut egr="pgr.fTKE>143 && pgr.fTKE<156";
  TCut elas="plas.fTKE>44 && plas.fTKE<68";
  TCut tc="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))>-20 && (tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))<20";
  TCut ac="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>-320 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<-20) || (tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>20 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<320)";

  tree->SetAlias("kF","sqrt(pow(pgr.GetPx()+plas.GetPx(),2.0)+pow(pgr.GetPy()+plas.GetPy(),2.0)+pow(pgr.GetPz()+plas.GetPz()-688.71661,2.0))");
  tree->SetAlias("Sx","226.0-pgr.fTKE-plas.fTKE");
  
}
