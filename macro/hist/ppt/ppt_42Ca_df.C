//void ppt_42Ca(double scale=1.0){
{
  double scale=1.0;


  TFile *file_42Ca = TFile::Open("output/calib_pid/hist_sx/ppt_42Ca.root");
  TH1F *sx=(TH1F*)file_42Ca->Get("sx")->Clone("sx");
  TH1F *sx0=(TH1F*)file_42Ca->Get("sx0")->Clone("sx0");  
  
  Double_t ymin=-0.0499/10.;
  Double_t ymax=1.499/10.;
  sx->Rebin(4);
  sx0->Rebin(4);
  
  sx->GetXaxis()->SetRange(sx->FindBin(15),sx->FindBin(40));
  
  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);  
  //sx->SetLabelSize(0.075/scale,"xy");
  sx->SetLabelSize(0.045,"xy");
  sx->SetTitleSize(0.045,"xy");  
  sx->SetTitle("");
  sx->GetXaxis()->SetTitle("#mbox{S_{X}} (MeV)");
  //sx->GetYaxis()->SetTitle("#mbox{d#sigma/dT_{p}d#Omega_{p}d#Omega_{X}} (#mbox{#mu}b/MeV#upoint str^{2}  per 200 keV)");
  sx->GetXaxis()->CenterTitle(true);
  sx->GetYaxis()->CenterTitle(true);
  
  sx->SetStats(0);
  sx0->SetStats(0);
  sx->Draw();
  sx0->Draw("same");
  
  Double_t St=19.690;
  Double_t E1=2522.75/1000.0;
  Double_t E2=3938.9/1000.0;
  Double_t E3=4095.6/1000.0;


  Double_t y0=0.15/10;
  TArrow a0(St,y0,St,y0+0.05/5,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St,y0+0.06/5,Form("#scale[%f]{gnd (3/2^{+})}",0.75*scale));

  Double_t y1=0.35/10;
  TArrow a1(St+E1,y1,St+E1,y1+0.05/5,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St+E1,y1+0.05/5,Form("#scale[%f]{2.52 MeV (1/2^{+})}",0.75*scale));

  Double_t y3=0.06;
  TArrow a3(St+E3,y3,St+E3,y3+0.05/5,0.01,"<|");
  a3.Draw();
  TLatex t3;
  t3.SetTextAlign(12);
  t3.SetTextAngle(90);
  t3.DrawLatex(St+E3,y3+0.05/5,Form("#scale[%f]{4.10 MeV (1/2^{+})}",0.75*scale));

  /*
  Double_t St_16O=25.032;
  Double_t E1_16O=2.3649;;
  TLatex t_16O;
  t_16O.SetTextAlign(12);
  t_16O.SetTextAngle(90);

  Double_t y0_16O=0.5/10;
  TArrow a0_16O(St_16O,y0_16O,St_16O,y0_16O+0.05/5,0.01,"<|");
  a0_16O.Draw();
  t_16O.DrawLatex(St_16O,y0_16O+0.06/5,Form("#scale[%f]{^{13}N}",0.75*scale));
  //Double_t y1_16O=0.3/10;
  //TArrow a1_16O(St_16O+E1_16O,y1_16O,St_16O+E1_16O,y1_16O+0.05/5,0.01,"<|");
  //a1_16O.Draw();
  //t_16O.DrawLatex(St_16O+E1_16O,y1_16O+0.06/5,Form("#scale[%f]{^{13}N}",0.75));

  Double_t E2_16O=3.547;
  Double_t y2_16O=0.8/10;
  TArrow a2_16O(St_16O+E2_16O,y2_16O,St_16O+E2_16O,y2_16O+0.05/5,0.01,"<|");                                                                                    
  a2_16O.Draw();                                                                                                                                                 
  t_16O.DrawLatex(St_16O+E2_16O,y2_16O+0.06/5,Form("#scale[%f]{^{13}N}",0.75*scale));
  */
  //gROOT->LoadMacro("macro/function/def_4gaus.C");

  double scale_16O=(0.21808865/(10.0/41.958))*0.449;
  double dx=sx->GetXaxis()->GetXmax()-sx->GetXaxis()->GetXmin();
  int Nbin=sx->GetXaxis()->GetNbins();


  TF1 *f_42Ca=new TF1("f_42Ca"
		      ,"([0]/sqrt(2.*TMath::Pi()*[2]*[2]))*exp(-0.5*pow((x-[1])/[2],2))",
		      20.5,24.0);
  TF1 *f_42Ca2=new TF1("f_42Ca2"
		       ,"([0]/sqrt(2.*TMath::Pi()*[2]*[2]))*exp(-0.5*pow((x-[1])/[2],2))",
		       24.0,26.0);

  f_42Ca->SetParameters(2.01936e-02,
			2.22809e+01,
			2.95277e-01);

  f_42Ca2->SetParameters(2.01936e-02,
			25.0,
			2.95277e-01);
  
  sx->Fit("f_42Ca","E","",20.5,24.0);
  sx->Fit("f_42Ca2","E","",24.0,25.6);

  double tdx=f_42Ca->GetParameter(0)/((double) dx/Nbin);
  double tdx_err=f_42Ca->GetParError(0)/((double) dx/Nbin);


  TF1 *f_42Ca_peak = new TF1("f_42Ca_peak",
			     "([0]/sqrt(2.*TMath::Pi()*[2]*[2]))*exp(-0.5*pow((x-[1])/[2],2))",
			     f_42Ca->GetParameter(1)-2.0,f_42Ca->GetParameter(1)+2.0); 
  f_42Ca_peak->SetParameters(f_42Ca->GetParameter(0),
                             f_42Ca->GetParameter(1),
                             f_42Ca->GetParameter(2));
  f_42Ca_peak->SetLineColor(2);
  f_42Ca_peak->SetLineWidth(0);
  //f_42Ca_peak->SetLineStyle(2);
  f_42Ca_peak->SetFillColor(2);
  f_42Ca_peak->SetFillStyle(3114);
  f_42Ca_peak->Draw("same C");

  double tdx_16O_gs=0.099611500;
  double tdx_16O_gs_err=0.028610100;
  
  TF1 *f_42Ca_peak2 = new TF1("f_42Ca_peak2",
			      "([0]/sqrt(2.*TMath::Pi()*[2]*[2]))*exp(-0.5*pow((x-[1])/[2],2))",
			      f_42Ca2->GetParameter(1)-2.0,f_42Ca2->GetParameter(1)+2.0); 
  f_42Ca_peak2->SetParameters(f_42Ca2->GetParameter(0)-tdx_16O_gs*((double) dx/Nbin)*scale_16O,
			      f_42Ca2->GetParameter(1),
			      f_42Ca2->GetParameter(2));
  f_42Ca_peak2->SetLineColor(2);
  f_42Ca_peak2->SetLineWidth(0);
  //f_42Ca_peak->SetLineStyle(2);
  f_42Ca_peak2->SetFillColor(2);
  f_42Ca_peak2->SetFillStyle(3114);
  f_42Ca_peak2->Draw("same C");

  f_42Ca->Draw("same");
  f_42Ca2->Draw("same");  
  

  TF1 *f_16O = new TF1("f_16O",
		       "([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",
		       -1000,1000);
  f_16O->SetParameters(0.1*((double) dx/Nbin)*scale_16O,2.48938e+01,
                       0.355*((double) dx/Nbin)*scale_16O,2.84556e+01,
                       f_42Ca->GetParameter(2));
  f_16O->SetLineColor(3);
  f_16O->SetLineStyle(2);
  f_16O->SetFillColor(3);  
  f_16O->SetFillStyle(3214);
  f_16O->Draw("same");

  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{42}Ca(#it{p,pt})^{39}K}",1.0*scale));
  //title.DrawLatex(.55,.725,Form("#scale[%f]{#it{S_{t}}=19.690 MeV}",0.8*scale));
  //title.DrawLatex(.55,.65,Form("#scale[%f]{TDX = %8.3f #pm %8.3f}",0.8*scale,tdx,tdx_err));

  std::cout << "TDX of 42Ca(p,pt) : " << tdx << " +/- " << tdx_err << std::endl;

  double tdx2=f_42Ca2->GetParameter(0)/(((double) dx/Nbin))-tdx_16O_gs*scale_16O;
  double tdx_err2=sqrt(pow(f_42Ca2->GetParError(0)/(((double) dx/Nbin)),2.0)+pow(tdx_16O_gs_err*scale_16O,2.0) );
  
  std::cout << "TDX of 42Ca(p,pt) : " << tdx2 << " +/- " << tdx_err2 << std::endl;
  
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
