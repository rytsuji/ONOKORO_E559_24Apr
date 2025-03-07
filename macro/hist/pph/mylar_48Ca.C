{
  TFile *file0 = TFile::Open("output/calib_pid/hist_sx/pph_48Ca_mylar.root");

  TF1 *f = new TF1("f","([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",0.0,50.0);

  f->SetParName(0,"const1");
  f->SetParName(1,"mean1");
  f->SetParName(2,"const2");
  f->SetParName(3,"mean2");
  f->SetParName(4,"sigma");


  sx->SetStats(0);
  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->cd();

  sx->GetXaxis()->SetTitle("S_{X} (MeV)");
  sx->GetYaxis()->SetTitle("TDX (#mu b/MeV sr^{2}) per 0.2 MeV");

  sx->Rebin(4);
  sx0->Rebin(4);  
  sx->Draw("E1");
  sx0->Draw("same");

  f->SetParameters(0.05,22.7,
		   0.35,26.2,
		   0.4);
  sx->Fit("f","","",22.0,28.0);

  TFile *file1 = TFile::Open("output/calib_pid/hist_sx/pph_48Ca_carbon.root");
  Double_t scale_carbon=0.66348429*(48.0080/10.47)/(12.0/10.65);
  sx->Rebin(4);
  sx0->Rebin(4);
  sx->Scale(scale_carbon);
  sx0->Scale(scale_carbon);
  sx0->Sumw2(0);
  sx->SetLineColor(3);
  sx->SetMarkerColor(3);
  sx0->SetLineColor(3);
  sx0->SetMarkerColor(3);
  sx->Draw("E1 same");
  sx0->Draw("same");
}
