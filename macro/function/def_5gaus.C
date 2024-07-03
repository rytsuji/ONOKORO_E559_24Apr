{

  
  TF1 *f = new TF1("f","([0]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[1])/[10],2))+([2]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[3])/[10],2))+([4]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[5])/[10],2))+([6]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[7])/[10],2))+([8]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[9])/[10],2))",-1000,1000);
  f->SetParName(0,"const1");
  f->SetParName(1,"mean1");
  f->SetParName(2,"const2");
  f->SetParName(3,"mean2");
  f->SetParName(4,"const3");
  f->SetParName(5,"mean3");
  f->SetParName(6,"const4");
  f->SetParName(7,"mean4");
  f->SetParName(8,"const5");
  f->SetParName(9,"mean5");
  f->SetParName(10,"sigma");
  
}
