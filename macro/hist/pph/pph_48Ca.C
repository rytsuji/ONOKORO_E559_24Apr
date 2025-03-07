//void ppt_48Ca(double scale=1.0){
{
  double scale=1.0;
  TFile *file_48Ca = TFile::Open("output/calib_pid/hist_sx/pph_48Ca_48Ca.root");  
  TH1F *sx=(TH1F*)file_48Ca->Get("sx")->Clone("sx");
  TH1F *sx0=(TH1F*)file_48Ca->Get("sx0")->Clone("sx0");
  
  Double_t ymin=-0.00499;
  Double_t ymax=0.1499;
  sx->Rebin(4);
  sx0->Rebin(4);  
  
  sx->GetXaxis()->SetRange(sx->FindBin(15),sx->FindBin(40));  
  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);

  sx->SetLabelSize(0.045,"xy");
  sx->SetTitleSize(0.045,"xy");
  sx->SetTitle("");
  sx->GetXaxis()->SetTitle("#mbox{S_{X}} (MeV)");
  //sx->GetYaxis()->SetTitle("#mbox{d#sigma/dT_{p}d#Omega_{p}d#Omega_{X}} (#mbox{#mu}b/MeV#upoint str^{2}  per 200 keV)");   

  sx->GetXaxis()->CenterTitle(true);
  sx->GetYaxis()->CenterTitle(true);
  sx->SetStats(0);
  sx->Draw();
  sx0->Draw("same");
  
  Double_t Sh=29.385; // 7/2-
  Double_t E1=1.660;
  Double_t E2=2.420;

  
  Double_t y0=0.01;
  TArrow a0(Sh,y0,Sh,y0+0.05/5,0.01,"<|");
  TArrow a0_1(Sh,y0+0.05/5,Sh-1.0,y0+0.10/5,0.01,"");
  a0.Draw();
  a0_1.Draw();   
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(Sh-1.0,y0+0.11/5,Form("#scale[%f]{gnd (7/2^{-})}",scale*0.75));

  Double_t y1=0.02;
  TArrow a1(Sh+E1,y1,Sh+E1,y1+0.05/5,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(Sh+E1,y1+0.05/5,Form("#scale[%f]{1.66 MeV}",scale*0.75));
  //t1.DrawLatex(Sh+E1+1.0,y1+0.05/5,Form("#scale[%f]{(1/2^{+})}",scale*0.75));

  Double_t y2=0.03;
  Double_t Sbg=3.00070e+01;
  TArrow a2(Sbg,y2,Sbg,y2+0.05/5,0.01,"<|");
  a2.Draw();
  TLatex t2;
  t2.SetTextAlign(12);
  t2.SetTextAngle(90);
  t2.DrawLatex(Sbg,y2+0.05/5,Form("#scale[%f]{^{13}C BG}",scale*0.75));
  
  TF1 *f_48Ca = new TF1("f_48Ca",
			"([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",
			-1000,1000);
  
  f_48Ca->SetParameters(0.02,30.0,
			0.01,31.0,
			0.00,0.00,
			0.4);
  f_48Ca->FixParameter(4,0.0);
  f_48Ca->FixParameter(5,0.0);
  sx->Fit("f_48Ca","E","",29.0,32.0);

  int Nbin=sx->GetXaxis()->GetNbins();
  double dx=sx->GetXaxis()->GetXmax()-sx->GetXaxis()->GetXmin();
  double tdx=f_48Ca->GetParameter(2)/((double) dx/Nbin);
  double tdx_err=f_48Ca->GetParError(2)/((double) dx/Nbin);

  double sigma=f_48Ca->GetParameter(6);
  TF1 *f_48Ca_peak = new TF1("f_48Ca_peak","gausn",f_48Ca->GetParameter(3)-2.0,f_48Ca->GetParameter(3)+2.0);
  f_48Ca_peak->SetParameters(f_48Ca->GetParameter(2),
			     f_48Ca->GetParameter(3),
			     sigma);
  f_48Ca_peak->SetLineColor(2);
  f_48Ca_peak->SetLineWidth(0);
  f_48Ca_peak->SetFillColor(2);
  f_48Ca_peak->SetFillStyle(3114);
  f_48Ca_peak->Draw("same C");

  double scale_16O=(0.21808865/(10.0/47.952))*0.329;
  TF1 *f_16O = new TF1("f_16O",
		       "([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",
		       -1000,1000);
  f_16O->SetParameters(0.107*((double) dx/Nbin)*scale_16O,2.28804e+01,
		       0.211*((double) dx/Nbin)*scale_16O,2.62719e+01,
		       sigma);
  f_16O->SetLineColor(3);
  f_16O->SetFillColor(3);  
  f_16O->SetLineStyle(2);
  f_16O->SetFillStyle(3214);  
  f_16O->Draw("same C");
  
  
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{48}Ca(#it{p,p}^{3}He)^{45}Ar}",1.0*scale));
  //title.DrawLatex(.55,.725,Form("#scale[%f]{#it{S_{t}}=24.996 MeV}",0.8*scale));
  //title.DrawLatex(.55,.65,Form("#scale[%f]{TDX = %8.3f #pm %8.3f}",0.8*scale,tdx,tdx_err));
  std::cout << "TDX of 48Ca(p,pt) : " << tdx << " +/- " << tdx_err << std::endl;
  
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
