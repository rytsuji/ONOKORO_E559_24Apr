{
  Double_t scale=1.0;
  TFile *file0 = TFile::Open("output/calib_pid/hist_sx/pph_carbon.root");
  sx->Rebin(4);
  sx0->Rebin(4);  

  Double_t ymin=-0.02;
  Double_t ymax=0.20;

  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);
  sx->GetXaxis()->SetRange(sx->FindBin(15),sx->FindBin(40));
  
  sx->SetStats(0);
  sx->SetLabelSize(0.045,"xy");
  sx->SetTitleSize(0.045,"xy");
  sx->SetTitle("");
  sx->GetXaxis()->SetTitle("#mbox{S_{X}} (MeV)");
  sx->GetXaxis()->CenterTitle(true);
  sx->GetYaxis()->CenterTitle(true);


  sx->Draw("E1");
  sx0->Draw("same");
  sx->Fit("gausn","","",15.0,27.5);

  Double_t St=26.280;
  Double_t y0=0.10;
  TArrow a0(St,y0,St,y0+0.05/5,0.01,"<|");
  a0.Draw();
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St,y0+0.06/5,Form("#scale[%f]{gnd (3/2^{-})}",scale*0.75));


  
}
