{
  TFile* file=TFile::Open("output/hist_phys/run2070.hist.root");
  TDirectoryFile* dir = (TDirectoryFile*)file->Get("phys");
  TH2F* h=(TH2F*)dir->Get("tke_las_gr");

  TCanvas *c1 =new TCanvas("c1","c1",800,800);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  h->SetStats(0);
  h->SetTitle("");
  h->GetXaxis()->SetTitle("");
  h->GetYaxis()->SetTitle("");

  h->GetXaxis()->SetRange(h->FindBin(142),h->FindBin(156));
  h->GetYaxis()->SetRange(h->FindBin(40),h->FindBin(80));

  h->Draw("colz");

  TLatex xtitle;  
  xtitle.SetTextAlign(22);
  xtitle.SetNDC(1);
  xtitle.SetTextAngle(0);
  xtitle.DrawLatex(0.5,0.05,"#scale[0.8]{#it{T_{GR}}}");

  TLatex ytitle;
  ytitle.SetTextAlign(22);
  ytitle.SetNDC(1);
  ytitle.SetTextAngle(90);
  ytitle.DrawLatex(0.05,0.5,"#scale[0.8]{#it{T_{LAS}}}");  


  TLatex tc;
  tc.SetTextAlign(22);
  tc.SetNDC(0);
  tc.DrawLatex(0.5,450,"#scale[0.8]{true coincidence}");
  
  
}
