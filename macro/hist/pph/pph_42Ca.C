//void ppt_42Ca(double scale=1.0){
{
  double scale=1.0;
  TFile *file_42Ca = TFile::Open("output/calib_pid/hist_sx/pph_42Ca.root");  
  TH1F *sx=(TH1F*)file_42Ca->Get("sx")->Clone("sx");
  TH1F *sx0=(TH1F*)file_42Ca->Get("sx0")->Clone("sx0");
  
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
  
  Double_t Sh=20.236; // 7/2-
  Double_t E1=1517.540/1000.0; //3/2+
  Double_t E2=2358.284/1000.0; //1/2+
  Double_t E3=2503.418/1000.0; //5/2+
  Double_t E4=2829.934/1000.0; //1/2+
  //Double_t E5=3973.1/1000.0; //5/2+
  
  Double_t y0=0.03;
  TArrow a0(Sh,y0,Sh,y0+0.05/5,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(Sh,y0+0.06/5,Form("#scale[%f]{gnd (7/2^{-})}",scale*0.75));

  Double_t y1=0.02;
  TArrow a1(Sh+E1,y1,Sh+E1,y1+0.05/5,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(Sh+E1,y1+0.05/5,Form("#scale[%f]{1.52 MeV (3/2^{+})}",scale*0.75));
  //t1.DrawLatex(Sh+E1+1.0,y1+0.05/5,Form("#scale[%f]{(3/2^{+})}",scale*0.75));

  Double_t y2=0.07;
  TArrow a2(Sh+E2,y2,Sh+E2,y2+0.05/5,0.01,"<|");
  a2.Draw();
  TLatex t2;
  t2.SetTextAlign(12);
  t2.SetTextAngle(90);
  t2.DrawLatex(Sh+E2,y2+0.05/5,Form("#scale[%f]{2.36 MeV (1/2^{+})}",scale*0.75));
  //t2.DrawLatex(Sh+E2+1.0,y2+0.05/5,Form("#scale[%f]{(1/2^{+})}",scale*0.75));

  double scale_16O=(0.21808865/(10.0/41.958))*0.449;
  int Nbin=sx->GetXaxis()->GetNbins();
  double dx=sx->GetXaxis()->GetXmax()-sx->GetXaxis()->GetXmin();


  
  TF1 *f_42Ca = new TF1("f_42Ca",
			"([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",
			-1000,1000);
  
  f_42Ca->SetParameters(0.05,21.5,
			0.10,Sh+E2,
			0.05,2.28804e+01,
			0.4);
  //f_42Ca->FixParameter(4,0.191*((double) dx/Nbin)*scale_16O);
  //f_42Ca->FixParameter(5,2.28804e+01);

  f_42Ca->SetParLimits(4,(0.191-0.028)*((double) dx/Nbin)*scale_16O,(0.191+0.028)*((double) dx/Nbin)*scale_16O);
  f_42Ca->SetParLimits(5,2.28804e+01-8.86089e-02,2.28804e+01+8.86089e-02);
  
  sx->Fit("f_42Ca","E","",21.0,23.5);
  double tdx=f_42Ca->GetParameter(2)/((double) dx/Nbin);
  double tdx_err=f_42Ca->GetParError(2)/((double) dx/Nbin);

  double sigma=f_42Ca->GetParameter(6);
  TF1 *f_42Ca_peak = new TF1("f_42Ca_peak","gausn",f_42Ca->GetParameter(3)-2.0,f_42Ca->GetParameter(3)+2.0);
  f_42Ca_peak->SetParameters(f_42Ca->GetParameter(2),
			     f_42Ca->GetParameter(3),
			     sigma);
  f_42Ca_peak->SetLineColor(2);
  f_42Ca_peak->SetLineWidth(0);
  f_42Ca_peak->SetFillColor(2);
  f_42Ca_peak->SetFillStyle(3114);
  f_42Ca_peak->Draw("same C");

  TF1 *f_16O = new TF1("f_16O",
		       "([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",
		       -1000,1000);
  f_16O->SetParameters(0.191*((double) dx/Nbin)*scale_16O,2.28804e+01,
		       0.503*((double) dx/Nbin)*scale_16O,2.62719e+01,
		       sigma);
  f_16O->SetLineColor(3);
  f_16O->SetFillColor(3);  
  f_16O->SetLineStyle(2);
  f_16O->SetFillStyle(3214);  
  f_16O->Draw("same C");
  
  
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{42}Ca(#it{p,p}^{3}He)^{39}Ar}",1.0*scale));
  //title.DrawLatex(.55,.725,Form("#scale[%f]{#it{S_{t}}=24.996 MeV}",0.8*scale));
  //title.DrawLatex(.55,.65,Form("#scale[%f]{TDX = %8.3f #pm %8.3f}",0.8*scale,tdx,tdx_err));
  std::cout << "TDX of 42Ca(p,ph) : " << tdx << " +/- " << tdx_err << std::endl;
  
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
