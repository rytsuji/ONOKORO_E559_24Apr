  double constant[5]={300.0,300.0,300.0,300.0,300.0};
  double mean[5]={-0.01,0.01,0.03,0.05,0.07};
  double sigma[5]={2.5e-03,2.5e-03,2.5e-03,2.5e-03,2.5e-03};
  TFile *_file0 = TFile::Open("output/gr/run1039.root");  
  TCut xcut="abs(gfp.fX+2.11515e+02)<10";
  TH1F *ha=new TH1F("ha","ha",1000,-0.1,0.1);
  tree->Draw("gfp.fA>>ha",xcut,"");
  TF1 *g5=new TF1("f","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)",-0.1,0.1);

  double constant[5]={300.0,300.0,300.0,300.0,300.0};
  double mean[5]={-0.045,-0.03,-0.01,0.01,0.03};
  double sigma[5]={2.5e-03,2.5e-03,2.5e-03,2.5e-03,2.5e-03};  
  for(int i=0; i<5; i++){
    f->SetParameter(3*i,constant[i]);
    f->SetParameter(3*i+1,mean[i]);    
    f->SetParameter(3*i+2,sigma[i]);    
  }
  ha->Fit("f");

  for(int i=0;i<5;i++){
    double val=f->GetParameter(3*i+1);
    std::cout <<   val << " " << (double) (i-2)*5/577.5 <<std::endl;
  }




}
