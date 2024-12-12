Double_t f(Double_t x);

void Fit_oxygen(Int_t run){

  TH1F *hoxygen =new TH1F("hoxygen","hoxygen",50,221,222);
  
  //tree->Draw("pgr.fTKE-f(gtgt.fA)>>hoxygen","abs(gtgt.fA+0.005)<0.005","");
  tree->Draw("pgr.fTKE-f(gtgt.fA)>>hoxygen","abs(gtgt.fA)<0.03","");


  TF1 *f=new TF1("f","gausn",-1000,1000);

  
  hoxygen->Fit("f","","",221.2,221.8);
  hoxygen->Fit("f","","",221.2,221.8);  

  Double_t BI=0.0;
  BI =  ScaData(run,4)*0.2;
    
  std::cout << "run" << run << std::endl;
  std::cout << f->GetParameter(0)/BI << std::endl;
 
  return;

}


Double_t f(Double_t x){return -18.4483*x-146.141*x*x;}
