Double_t corr(Double_t x);

void Fit_oxygen_42Ca(Int_t run){

  TH1F *hoxygen =new TH1F("hoxygen","hoxygen",50,221,222);
  
  tree->Draw("pgr.fTKE-corr(gtgt.fA)>>hoxygen","abs(gtgt.fA+0.005)<0.005","");

    TF1 *f = new TF1("f","([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",-600,600);
  f->SetParName(0,"const1");
  f->SetParName(1,"mean1");
  f->SetParName(2,"const2");
  f->SetParName(3,"mean2");
  f->SetParName(4,"const3");
  f->SetParName(5,"mean3");
  f->SetParName(6,"sigma");



  f->SetParameters(100,221.3,
		   300,221.6,
		   30,221.8,
		   0.1);
  
  hoxygen->Fit("f","","",221.25,221.9);
  hoxygen->Fit("f","","",221.25,221.9);  

  Double_t BI=0.0;
  BI =  ScaData(run,4)*0.2;
    
  std::cout << "run" << run << std::endl;
  std::cout << f->GetParameter(2)/BI << std::endl;
 
  return;

}


Double_t corr(Double_t x){return -18.4483*x-146.141*x*x;}
