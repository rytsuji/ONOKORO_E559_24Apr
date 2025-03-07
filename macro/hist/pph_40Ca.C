{
  double scale=1;
  TFile *file_40Ca = TFile::Open("output/calib_pid/hist_sx/pph_40Ca.root");
  

  Double_t ymin=-0.0499/10;
  Double_t ymax=1.499/10;

  sx->Rebin(4);
  sx0->Rebin(4);
  
  sx->GetXaxis()->SetRange(sx->FindBin(15),sx->FindBin(40));
  //sx->GetXaxis()->SetTitle("S_{X} (MeV)"); 
  //sx->GetYaxis()->SetTitle("#it{d#sigma/dE_{p}d#Omega_{p}d#Omega_{X}dS_{X}} (#it{#mu}b/MeV#upoint str^{2}  per 200 keV)");
  
  sx->GetXaxis()->SetTitle("S_{X} (MeV)");
  sx->GetYaxis()->SetTitle("TDX (#mu b/MeV sr^{2}) per 0.2 MeV");


  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);

  //sx->SetLabelSize(0.075*scale,"xy");  

  sx->SetStats(0);
  sx0->SetStats(0);
  sx->Draw();
  sx0->Draw("same");
  
  Double_t Sh=18.830; // 3/2+                                                                                                                              
  Double_t E1=1409.84/1000.0; //1/2+                                                                                                                         
  Double_t E2=2796.16/1000.0; //7/2+
  Double_t E3=3170.0/1000.0; //5/2+  
  Double_t E4=3601.8/1000.0; //5/2+
  Double_t E5=3973.1/1000.0; //5/2+  


  Double_t y0=0.2/10;
  TArrow a0(Sh,y0,Sh,y0+0.05/5,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(Sh,y0+0.06/5,Form("#scale[%f]{gnd (3/2^{+})}",scale*0.75));

  Double_t y1=1.0/10;
  TArrow a1(Sh+E1,y1,Sh+E1,y1+0.05/5,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(Sh+E1-1.0,y1+0.06/5,Form("#scale[%f]{1.40 MeV}",scale*0.75));
  t1.DrawLatex(Sh+E1+0.5,y1+0.06/5,Form("#scale[%f]{(1/2^{+})}",scale*0.75));

  Double_t y2=0.10/10;
  TArrow a2(Sh+E2,y2,Sh+E2,y2+0.05/5,0.01,"<|");
  //a2.Draw();
  TLatex t2;
  t2.SetTextAlign(12);
  t2.SetTextAngle(90);
  //t2.DrawLatex(Sh+E2+0.25,y2+0.07,"#scale[1.2]{7/2^{+}}");

  Double_t y3=0.10/10;
  TArrow a3(Sh+E3,y3,Sh+E3,y3+0.05/5,0.01,"<|");
  //a3.Draw();
  TLatex t3;
  t3.SetTextAlign(12);
  t3.SetTextAngle(90);
  //t3.DrawLatex(Sh+E3+1.0,y3+0.07,"#scale[1.2]{5/2^{+}}");

  Double_t y4=0.10/10;
  TArrow a4(Sh+E4,y3,Sh+E4,y4+0.05/5,0.01,"<|");
  //a4.Draw();
  TLatex t4;
  t4.SetTextAlign(12);
  t4.SetTextAngle(90);
  //t4.DrawLatex(Sh+E4+1.0,y4+0.07,"#scale[1.2]{5/2^{+}}");


  Double_t St_16O=22.793;
  Double_t E1_16O=3089.443/1000.;
  TLatex t_16O;
  t_16O.SetTextAlign(12);
  t_16O.SetTextAngle(90);

  Double_t y0_16O=0.15/10;
  TArrow a0_16O(St_16O,y0_16O,St_16O,y0_16O+0.05/5,0.01,"<|");
  a0_16O.Draw();
  t_16O.DrawLatex(St_16O,y0_16O+0.06/5,Form("#scale[%f]{^{13}C}",0.75*scale));
  Double_t y1_16O=0.28/10;
  TArrow a1_16O(St_16O+E1_16O,y1_16O,St_16O+E1_16O,y1_16O+0.05/5,0.01,"<|");
  a1_16O.Draw();
  t_16O.DrawLatex(St_16O+E1_16O,y1_16O+0.06/5,Form("#scale[%f]{^{13}C}",0.75*scale));  

  
  TF1 *f_40Ca = new TF1("f_40Ca","([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",-1000,1000);

  //TF1 *f_40Ca = new TF1("f_40Ca","([0]/sqrt(2.*TMath::Pi()*[12]*[12]))*exp(-0.5*pow((x-[1])/[12],2))+([2]/sqrt(2.*TMath::Pi()*[12]*[12]))*exp(-0.5*pow((x-[3])/[12],2))+([4]/sqrt(2.*TMath::Pi()*[12]*[12]))*exp(-0.5*pow((x-[5])/[12],2))+([6]/sqrt(2.*TMath::Pi()*[12]*[12]))*exp(-0.5*pow((x-[7])/[12],2))+([8]/sqrt(2.*TMath::Pi()*[12]*[12]))*exp(-0.5*pow((x-[9])/[12],2))+([10]/sqrt(2.*TMath::Pi()*[12]*[12]))*exp(-0.5*pow((x-[11])/[12],2))",-1000,1000);

  f_40Ca->SetParameters(0.01,19.2,
			0.1,20.4,
			0.02,21.5,
			0.35);
  
  sx->Fit("f_40Ca","E","",18.75,22.0);
  
  double dx=sx->GetXaxis()->GetXmax()-sx->GetXaxis()->GetXmin();
  int Nbin=sx->GetXaxis()->GetNbins();
  double tdx=f_40Ca->GetParameter(2)/((double) dx/Nbin);
  double tdx_err=f_40Ca->GetParError(2)/((double) dx/Nbin);

  TF1 *f_40Ca_peak = new TF1("f_40Ca_peak","gausn",f_40Ca->GetParameter(3)-2.0,f_40Ca->GetParameter(3)+2.0);
  f_40Ca_peak->SetParameters(f_40Ca->GetParameter(2),
                             f_40Ca->GetParameter(3),
                             f_40Ca->GetParameter(6));

  f_40Ca_peak->SetLineColor(1);
  f_40Ca_peak->SetLineWidth(1);
  f_40Ca_peak->SetLineStyle(2);
  f_40Ca_peak->SetFillColor(1);
  f_40Ca_peak->SetFillStyle(3001);
  f_40Ca_peak->Draw("same C");

  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{40}Ca(#it{p,p}^{3}He)}",scale*1.0));
  title.DrawLatex(.55,.725,Form("#scale[%f]{#it{S}_{^{3}He}=18.830 MeV}",scale*0.8));
  title.DrawLatex(.55,.65,Form("#scale[%f]{TDX = %8.3f #pm %8.3f}",scale*0.8,tdx,tdx_err));
  
}
