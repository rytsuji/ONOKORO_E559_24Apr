{
  //

  TFile *file_carbon = TFile::Open("output/ppx/ppt_carbon.tra_ave.root ");  

  Double_t ymin=-0.0499;
  Double_t ymax=1.3999;
  
  //sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(18),sx_tave->FindBin(38));
  
  sx_tave->SetMinimum(ymin);
  sx_tave->SetMaximum(ymax);

  sx_tave->SetLabelSize(0.06,"y");
  
  sx_tave->SetStats(0);
  sx_tave0->SetStats(0);

  sx_tave->GetXaxis()->SetTitle("S_{X} (MeV)");
  sx_tave->GetYaxis()->SetTitle("#scale[0.8]{#it{d#sigma/dE_{p}d#Omega_{p}d#Omega_{X}dS_{X}} (#it{#mu}b/MeV#upoint str^{2}  per 200 keV)}");
  
  sx_tave->Draw();
  sx_tave0->Draw("same");
  
  Double_t St=27.366;                                                                                                                              

  Double_t y0=1.0;
  TArrow a0(St,y0,St,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St,y0+0.06,"#scale[0.75]{gnd (3/2^{+})}");

  


  TF1 *f_carbon = new TF1("f_carbon","gausn(0)",0,50);
  
  sx_tave->Fit("f_carbon","E","",26,28);

  int Nbin=sx_tave->GetXaxis()->GetNbins();
  double tdx=f_carbon->GetParameter(0)/((double) 50.0/Nbin);
  double tdx_err=f_carbon->GetParError(0)/((double) 50.0/Nbin);
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,"#scale[1.0]{^{12}C#it{(p,pt)}}");
  title.DrawLatex(.65,.725,"#scale[0.8]{#it{S_{t}}=27.366 MeV}");
  title.DrawLatex(.60,.65,Form("#scale[0.8]{TDX = %8.3f #pm %8.3f}",tdx,tdx_err));

  
  /*
  TText *t = new TText(.5,.5,"Preliminary");
  t->SetNDC(1);
  t->SetTextAlign(22);
  t->SetTextColorAlpha(kRed, 0.9);
  t->SetTextFont(43);
  t->SetTextSize(40);
  t->SetTextAngle(-45);
  t->Draw("same");
  */  
}
