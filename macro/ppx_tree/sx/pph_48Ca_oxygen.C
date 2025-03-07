{
  TFile *file_mylar = TFile::Open("output/calib_pid/hist_sx/pph_48Ca_mylar.root ");
  TFile *file_carbon = TFile::Open("output/calib_pid/hist_sx/pph_48Ca_carbon.root ");
      
  TH1F *h_mylar = (TH1F*)file_mylar->Get("sx")->Clone("h_mylar");
  TH1F *h_mylar0 = (TH1F*)file_mylar->Get("sx0")->Clone("h_mylar0");
  TH1F *h_carbon = (TH1F*)file_carbon->Get("sx")->Clone("h_carbon");
  TH1F *h_carbon0 = (TH1F*)file_carbon->Get("sx0")->Clone("h_carbon0");
  TH1F *h_oxygen = (TH1F*)file_mylar->Get("sx")->Clone("h_oxygen");
  TH1F *h_oxygen0 = (TH1F*)file_mylar->Get("sx0")->Clone("h_oxygen0");


  
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
  
  h_oxygen->Add(h_carbon,-1.0);
  h_oxygen0->Add(h_carbon0,-1.0);    


  h_mylar->Rebin(4);
  h_mylar0->Rebin(4);
  h_carbon->Rebin(4);
  h_carbon0->Rebin(4);
  h_oxygen->Rebin(4);
  h_oxygen0->Rebin(4);

  
  h_carbon0->Sumw2(0);
  h_mylar0->Sumw2(0);
  h_oxygen0->Sumw2(0);



  
}
