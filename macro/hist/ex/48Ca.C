{
  Int_t rebin=20; //1MeV

  double scale_mylar=(0.21808865/(10.0/47.952))*0.329;
  double scale_carbon=scale_mylar*0.66348429*(48.0080/10.47)/(12.0/10.65);

  Double_t xmin = -1.0;
  Double_t xmax = 20.0;
  Double_t ymin = -0.025;
  Double_t ymax = 0.2;
  
  
  TFile *file_mylar_t  = TFile::Open("output/calib_pid/hist_ex/ppt_mylar_48Ca.root ");
  TFile *file_carbon_t = TFile::Open("output/calib_pid/hist_ex/ppt_carbon_48Ca.root ");
  TFile *file_Ca_t     = TFile::Open("output/calib_pid/hist_ex/ppt_48Ca_48Ca.root ");

  TFile *file_mylar_h  = TFile::Open("output/calib_pid/hist_ex/pph_48Ca_mylar_48Ca.root ");
  TFile *file_carbon_h = TFile::Open("output/calib_pid/hist_ex/pph_48Ca_carbon_48Ca.root ");
  TFile *file_Ca_h     = TFile::Open("output/calib_pid/hist_ex/pph_48Ca_48Ca_48Ca.root ");

  TH1F *h_mylar_t = (TH1F*)file_mylar_t->Get("sx")->Clone("h_mylar_t");
  TH1F *h_carbon_t = (TH1F*)file_carbon_t->Get("sx")->Clone("h_carbon_t");
  TH1F *h_Ca_t_raw = (TH1F*)file_Ca_t->Get("sx")->Clone("h_Ca_t_raw");

  TH1F *h_mylar_h = (TH1F*)file_mylar_h->Get("sx")->Clone("h_mylar_h");
  TH1F *h_carbon_h = (TH1F*)file_carbon_h->Get("sx")->Clone("h_carbon_h");
  TH1F *h_Ca_h_raw = (TH1F*)file_Ca_h->Get("sx")->Clone("h_Ca_h_raw");
  

  TH1F *h_Ca_t=(TH1F*) h_Ca_t_raw->Clone("h_Ca_t"); 
  h_Ca_t->Add(h_mylar_t,-scale_mylar);
  h_Ca_t->Add(h_carbon_t,scale_carbon);
  h_Ca_t->Rebin(rebin);
  TH1F *h_Ca_t0=(TH1F*) h_Ca_t->Clone("h_Ca_t0");
  h_Ca_t0->Sumw2(0);

  TH1F *h_Ca_h=(TH1F*) h_Ca_h_raw->Clone("h_Ca_h"); 
  h_Ca_h->Add(h_mylar_h,-scale_mylar);
  h_Ca_h->Add(h_carbon_h,scale_carbon);
  h_Ca_h->Rebin(rebin);
  h_Ca_h->Scale(1.0/1.65); ///Scaling elementary process
  TH1F *h_Ca_h0=(TH1F*) h_Ca_h->Clone("h_Ca_h0");
  h_Ca_h0->Sumw2(0);

  h_Ca_t->SetTitle("");
  h_Ca_t->GetXaxis()->SetTitle("#mbox{E_{X}} (MeV)");
  h_Ca_t->SetLabelSize(0.045,"xy");
  h_Ca_t->SetTitleSize(0.045,"xy");
  h_Ca_t->GetXaxis()->CenterTitle(true);
  h_Ca_t->GetYaxis()->CenterTitle(true);
  h_Ca_t->SetStats(0);

  h_Ca_t->GetXaxis()->SetRange(h_Ca_t->FindBin(xmin), h_Ca_t->FindBin(xmax));
  h_Ca_t->SetMinimum(ymin);
  h_Ca_t->SetMaximum(ymax);

  
  h_Ca_t->SetLineColor(2);
  h_Ca_t->SetMarkerColor(2);
  h_Ca_t0->SetLineColor(2);
  h_Ca_t0->SetMarkerColor(2);

  h_Ca_t->SetLineWidth(3);
  h_Ca_h->SetLineWidth(2);
  h_Ca_t0->SetLineWidth(3);
  h_Ca_h0->SetLineWidth(2);
  
  h_Ca_t->Draw("");
  h_Ca_t0->Draw("same");
  h_Ca_h->Draw("same");
  h_Ca_h0->Draw("same");
}
