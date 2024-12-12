{

  double scale=1;
  TFile *file_mylar = TFile::Open("output/ppx_ex_nogate/pph_48Ca_mylar_48Ca.root ");  
  TFile *file_carbon = TFile::Open("output/ppx_ex_nogate/pph_48Ca_carbon_48Ca.root ");
  TFile *file_48Ca = TFile::Open("output/ppx_ex_nogate/pph_48Ca_48Ca_48Ca.root ");  
    
  Double_t ymin=-0.0099;
  Double_t ymax=0.0999;
  
  TH1F *h_mylar = (TH1F*)file_mylar->Get("sx")->Clone("h_mylar");
  TH1F *h_mylar0 = (TH1F*)file_mylar->Get("sx0")->Clone("h_mylar0");
  TH1F *h_carbon = (TH1F*)file_carbon->Get("sx")->Clone("h_carbon");
  TH1F *h_carbon0 = (TH1F*)file_carbon->Get("sx0")->Clone("h_carbon0");
  TH1F *h_oxygen = (TH1F*)file_mylar->Get("sx")->Clone("h_oxygen");
  TH1F *h_oxygen0 = (TH1F*)file_mylar->Get("sx0")->Clone("h_oxygen0");
  TH1F *h_48Ca = (TH1F*)file_48Ca->Get("sx")->Clone("h_48Ca");
  TH1F *h_48Ca0 = (TH1F*)file_48Ca->Get("sx0")->Clone("h_48Ca0");
  TH1F *h_48Ca_raw = (TH1F*)file_48Ca->Get("sx")->Clone("h_48Ca_raw");
  TH1F *h_48Ca0_raw = (TH1F*)file_48Ca->Get("sx0")->Clone("h_48Ca0_raw");   
  
  Double_t scale_carbon=0.66348429*(48.0080/10.47)/(12.0/10.65);
  h_carbon->Scale(scale_carbon);
  h_carbon0->Scale(scale_carbon);
  h_carbon->SetLineColor(2);
  h_carbon0->SetLineColor(2);
  h_carbon0->SetMarkerColor(2);

  h_oxygen->SetLineColor(2);
  h_oxygen0->SetLineColor(2);
  h_oxygen0->SetMarkerColor(2);
  
  h_mylar->SetStats(0);
  h_mylar0->SetStats(0);
  h_carbon->SetStats(0);
  h_carbon0->SetStats(0);
  h_oxygen->SetStats(0);
  h_oxygen0->SetStats(0);
  h_48Ca->SetStats(0);
  h_48Ca0->SetStats(0);
  h_48Ca_raw->SetStats(0);
  h_48Ca0_raw->SetStats(0);
  
  h_oxygen->Add(h_carbon,-1.0);
  h_oxygen0->Add(h_carbon0,-1.0);  

  Double_t scale_oxygen_48Ca=(0.21808865/(10.0/47.952))*0.329;//*(1.3272349);
  h_oxygen->Scale(scale_oxygen_48Ca);
  h_oxygen0->Scale(scale_oxygen_48Ca);

  h_48Ca->Add(h_oxygen,-1);
  h_48Ca0->Add(h_oxygen0,-1);
  
  TH1F *sx = (TH1F*) h_48Ca->Clone("sx");
  TH1F *sx0 = (TH1F*) h_48Ca0->Clone("sx0");   
  

  h_48Ca->Rebin(16);
  h_48Ca0->Rebin(16);
  h_oxygen->Rebin(16);
  h_oxygen0->Rebin(16);
  h_48Ca_raw->Rebin(16);
  h_48Ca0_raw->Rebin(16);



  h_mylar0->Sumw2(0);
  h_carbon0->Sumw2(0);
  
  h_oxygen0->Sumw2(0);
  h_48Ca0->Sumw2(0);
  
  h_48Ca->Draw();
  h_48Ca0->Draw("same");  

  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{48}Ca(#it{p,p}^{3}He)}",1.0*scale));


  TFile *fout = new TFile("output/ppx_ex_nogate/pph_48Ca.root","RECREATE");
  h_48Ca->Write();
  h_48Ca0->Write();
  h_48Ca_raw->Write();
  h_48Ca0_raw->Write();
  h_oxygen->Write();
  h_oxygen0->Write();
  sx->Write();
  sx0->Write();
}
