{

  TF1 *f = new TF1("f","([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",-1000,1000);
  f->SetParName(0,"const1");
  f->SetParName(1,"mean1");
  f->SetParName(2,"const2");
  f->SetParName(3,"mean2");
  f->SetParName(4,"sigma");
  
  f->SetParameters(140,26.1,80,27.6,0.25);
  sx_nogate->Fit("f","","",25.5,28.0);
  sx->Fit("f","","",25.5,28.0);
  sxg->Fit("f","","",25.5,28.0);

  double const1=f->GetParameter(0);
  double mean1=f->GetParameter(1);
  double const2=f->GetParameter(2);
  double mean2=f->GetParameter(3);
  double sigma=f->GetParameter(4);

  

  //TF1 *g1 = new TF1("g1","([0]/sqrt(2.*TMath::Pi()*[2]*[2]))*exp(-0.5*pow((x-[1])/[2],2))",-1000,1000);
  //TF1 *g2 = new TF1("g2","([0]/sqrt(2.*TMath::Pi()*[2]*[2]))*exp(-0.5*pow((x-[1])/[2],2))",-1000,1000);
  //g1->SetParameters(const1,mean1,sigma);
  //g2->SetParameters(const2,mean2,sigma);

  //g1->SetLineColor(kBlack);
  //g1->SetLineStyle(2);
  //g2->SetLineColor(kBlack);
  //g2->SetLineStyle(2);
}
