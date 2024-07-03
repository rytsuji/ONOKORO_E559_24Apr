{

  
  TF1 *f = new TF1("f","([0]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[1])/[8],2))+([2]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[3])/[8],2))+([4]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[5])/[8],2))+([6]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[7])/[8],2))",-1000,1000);
  f->SetParName(0,"const1");
  f->SetParName(1,"mean1");
  f->SetParName(2,"const2");
  f->SetParName(3,"mean2");
  f->SetParName(4,"const3");
  f->SetParName(5,"mean3");
  f->SetParName(6,"const4");
  f->SetParName(7,"mean4");
  f->SetParName(8,"sigma");
  
}
