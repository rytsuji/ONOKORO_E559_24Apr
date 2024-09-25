{

  Double_t scale=0.66348429*(48.0080/10.47)/(12.0/10.65); 
  //scale=2.0;
  TFile *file_mylar=TFile::Open("output/ppx/ppt_mylar.tra_ave.root");
  TFile *file_carbon=TFile::Open("output/ppx/ppt_carbon.tra_ave.root");

  //TFile *fout = new TFile(Form("output/ppx/ppt_oxygen.root"),"RECREATE");
  TH1F *h_oxygen;
  TH1F *h_oxygen0;  
  TH1F *h_mylar   =( (TH1F*) file_mylar->Get("sx_tave"));
  TH1F *h_mylar0  =( (TH1F*) file_mylar->Get("sx_tave0"));
  TH1F *h_carbon  =( (TH1F*) file_carbon->Get("sx_tave"));
  TH1F *h_carbon0 =( (TH1F*) file_carbon->Get("sx_tave0"));

  int Nbin=h_mylar->GetXaxis()->GetNbins();
  double xmin=h_mylar->GetXaxis()->GetXmin();
  double xmax=h_mylar->GetXaxis()->GetXmax();    
  
  h_oxygen   = new TH1F("h_oxygen","h_oxygen",Nbin,xmin,xmax);
  h_oxygen0  = new TH1F("h_oxygen0","h_oxygen0",Nbin,xmin,xmax);  
  h_oxygen->Sumw2();
  h_oxygen0->Sumw2(0);  
  
  h_oxygen->Add(h_mylar,1.0);
  h_oxygen->Add(h_carbon,-scale);

  h_oxygen0->Add(h_mylar0,1.0);
  h_oxygen0->Add(h_carbon0,-scale);  

  //h_mylar->Write();
  //h_mylar0->Write();

  //h_carbon->Write();
  //h_carbon0->Write();

  //h_oxyegn->Write();
  //h_oxygen0->Write();

  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht h_oxygen");
  gApplication->ProcessLine("ht h_oxygen0 same");  
}
