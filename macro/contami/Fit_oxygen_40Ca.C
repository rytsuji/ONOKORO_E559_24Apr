Double_t f(Double_t x);

void Fit_oxygen_40Ca(){
  Int_t run=2054;
  TH1F *hoxygen =new TH1F("hoxygen","hoxygen",50,221,222);
  
  tree->Draw("pgr.fTKE-f(gtgt.fA)>>hoxygen","abs(gtgt.fA)<0.03","");


  TF1 *g = new TF1("g","([0]/sqrt(2.*TMath::Pi()*[2]*[2]))*exp(-0.5*pow((x-[1])/[2],2))+[3]",-1000,1000);

  g->SetParameters(100,221.5,0.2,0);
  hoxygen->Fit("g","","",221.2,221.7);
  //hoxygen->Fit("g","","",221.2,221.7);  

  Double_t BI=0.0;
  BI =  ScaData(run,4)*0.2;
    
  std::cout << "run" << run << std::endl;
  std::cout << g->GetParameter(0)/BI << std::endl;
  
  return;

}


Double_t f(Double_t x){return -18.4483*x-146.141*x*x;}
