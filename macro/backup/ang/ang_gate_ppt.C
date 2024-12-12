{
  TCut ang_gr="abs(pgr.GetTheta()-51.2)<1.0 && abs(pgr.GetPhi())<3.5 && abs(pgr.GetPhi())<(4.0*pgr.GetTheta()-199.3) && abs(pgr.GetPhi())<(-5.0*pgr.GetTheta()+262.5)";
  TCut ang_las="abs(plas.GetTheta()-50.9)<3.4 && abs(fmod(plas.GetPhi()+360.0,360.0)-180)<4";
    
}
