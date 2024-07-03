{
  TFile* file=TFile::Open("output/hist_phys/run2070.hist.root");
  TDirectoryFile* dir = (TDirectoryFile*)file->Get("phys");
  TH1F* h=(TH1F*)dir->Get("tof");

  TCanvas *c1 =new TCanvas("c1","c1",800,600);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  h->SetStats(0);
  h->SetTitle("");
  h->GetXaxis()->SetTitle("");
  h->GetYaxis()->SetTitle("");

  h->GetXaxis()->SetRange(h->FindBin(-700),h->FindBin(500));
  h->SetMinimum(0);
  h->SetMaximum(500);
  h->Draw();

  b=new TBox(-20,0,20,400);
  b->SetLineColor(2);
  b->SetFillStyle(0);
  b->Draw();

  TLatex xtitle;
  xtitle.SetTextAlign(22);
  xtitle.SetNDC(1);
  xtitle.SetTextAngle(0);
  xtitle.DrawLatex(0.5,0.05,"#scale[0.8]{TOF_{GR-LAS} -#it{(#frac{L_{GR}}{#beta_{GR}}-#frac{L_{LAS}}{#beta_{LAS}})}}");

  TLatex ytitle;
  ytitle.SetTextAlign(22);
  ytitle.SetNDC(1);
  ytitle.SetTextAngle(90);
  ytitle.DrawLatex(0.05,0.5,"#scale[0.8]{count}");

  TLatex tc;
  tc.SetTextAlign(22);
  tc.SetNDC(0);
  tc.DrawLatex(0.5,450,"#scale[0.8]{true coincidence}");
  
  
}
