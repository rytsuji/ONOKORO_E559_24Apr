{
  int req=0;
  int acc=0;  
  TRandom3 r;
  double x[3];

  for(int i=0;i<100000000;i++){
    req++;
    r.Sphere(x[0],x[1],x[2],1);
    TVector3 p_lab(x[0],x[1],x[2]);
    
    if(abs(p_lab.Theta()*TMath::RadToDeg()-51.2)<1.0 &&
       abs(p_lab.Phi()*TMath::RadToDeg())<3.5 &&
       abs(p_lab.Phi()*TMath::RadToDeg())<(4.0*p_lab.Theta()*TMath::RadToDeg()-199.3) &&
       abs(p_lab.Phi()*TMath::RadToDeg())<(-5.0*p_lab.Theta()*TMath::RadToDeg()+262.5) ) acc++;  
  }

  std::cout <<4.0*TMath::Pi()* (double) acc/req << std::endl;
  
}
