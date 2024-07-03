{

  
  TF1 *f = new TF1("f","([0]/sqrt(2.*TMath::Pi()*[5]*[5]))*exp(-0.5*pow((x-[4])/[5],2))+([1]/sqrt(2.*TMath::Pi()*[5]*[5]))*exp(-0.5*pow((x-[4]-0.47445)/[5],2))+([2]/sqrt(2.*TMath::Pi()*[5]*[5]))*exp(-0.5*pow((x-[4]-1.0507050)/[5],2))+([3]/sqrt(2.*TMath::Pi()*[5]*[5]))*exp(-0.5*pow((x-[4]-1.4491)/[5],2))",-1000,1000);
  f->SetParName(0,"const1");
  f->SetParName(1,"const2");
  f->SetParName(2,"const3");
  f->SetParName(3,"const4");
  f->SetParName(4,"mean_gs");
  f->SetParName(5,"sigma");

  f->SetParameters(60,140,60,180,22.1,0.3);
  f->SetParLimits(0,0.0,1000.0);
  f->SetParLimits(1,0.0,1000.0);
  f->SetParLimits(2,0.0,1000.0);
  f->SetParLimits(3,0.0,1000.0);
  f->SetParLimits(4,0.0,1000.0);
  f->SetParLimits(5,0.2,0.5);
  sx->Fit("f","","",20,25.3)

    
}
