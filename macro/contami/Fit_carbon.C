Double_t f(Double_t x);

void Fit_carbon(Int_t run){

  TH1F *hcarbon =new TH1F("hcarbon","hcarbon",50,219.0,220.5);
  
  tree->Draw("pgr.fTKE-f(gtgt.fA)>>hcarbon","abs(gtgt.fA)<0.015","");

  TF1 *f=new TF1("f","gausn",-1000,1000);
  
  hcarbon->Fit("f","","",219.5,220.1);
  hcarbon->Fit("f","","",219.5,220.1);

  Double_t BI=0.0;
  //  for(int i=0;i<4;i++){ 
  //BI=0.25*1.3260702* (Double_t) ScaData(run,28+i);
  //}
  BI =  ScaData(run,4)*0.2;
    
  std::cout << "run" << run << std::endl;
  std::cout << f->GetParameter(0)/BI << std::endl;
  
  return;

}


Double_t f(Double_t x){return -23.965*x-183.202*x*x;}
