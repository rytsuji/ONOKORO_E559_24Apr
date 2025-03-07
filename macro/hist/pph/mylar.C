{
  Double_t scale=1.0;
  TFile *file0 = TFile::Open("output/calib_pid/hist_sx/pph_mylar.root");

  TF1 *f = new TF1("f","([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",0.0,50.0);

  f->SetParName(0,"const1");
  f->SetParName(1,"mean1");
  f->SetParName(2,"const2");
  f->SetParName(3,"mean2");
  f->SetParName(4,"sigma");

  sx->Rebin(4);
  sx0->Rebin(4);

  Double_t ymin=-0.02;
  Double_t ymax=0.60;

  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);
  sx->GetXaxis()->SetRange(sx->FindBin(15),sx->FindBin(40));

  sx->SetStats(0);
  sx->SetTitle("");
  sx->GetXaxis()->SetTitle("#mbox{S_{X}} (MeV)");
  sx->GetXaxis()->CenterTitle(true);
  sx->GetYaxis()->CenterTitle(true);

  

  
  sx->Draw("E1");
  sx0->Draw("same");

  f->SetParameters(0.05,22.7,
		   0.35,26.2,
		   0.4);
  sx->Fit("f","","",20.5,27.25);
  
  TFile *file1 = TFile::Open("output/calib_pid/hist_sx/pph_carbon.root");
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
  
  Double_t St0=22.793;
  Double_t y0=0.1;
  TArrow a0(St0,y0,St0,y0+0.02,0.01,"<|");
  a0.Draw();
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St0,y0+0.03,Form("#scale[%f]{gnd (1/2^{-})}",scale*0.75));

  Double_t St1=26.477;
  Double_t y1=0.40;
  TArrow a1(St1,y1,St1,y1+0.02,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St1,y1+0.03,Form("#scale[%f]{3.68 MeV}",scale*0.75));
  t1.DrawLatex(St1+1.0,y1+0.03,Form("#scale[%f]{(3/2^{-})}",scale*0.75));  
}
