{
  TFile *file0 = TFile::Open("output/calib_pid/hist_sx/pph_48Ca_carbon.root");


  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->cd();
  sx->SetStats(0);
  sx->GetXaxis()->SetTitle("S_{X} (MeV)");
  sx->GetYaxis()->SetTitle("TDX (#mu b/MeV sr^{2}) per 0.2 MeV");

  sx->Rebin(4);
  sx0->Rebin(4);  
  sx->Draw("E1");
  sx0->Draw("same");
  sx->Fit("gausn","","",15.0,27.0)


  
}
