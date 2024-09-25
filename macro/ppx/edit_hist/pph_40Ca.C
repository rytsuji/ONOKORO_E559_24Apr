{
  double scale=1/(1.0-0.05/(0.21250000+0.05));
  TFile *file_40Ca = TFile::Open("output/ppx/pph_40Ca.tra_ave.root ");
  

  Double_t ymin=-0.0499;
  Double_t ymax=0.9999;
  
  //sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(15),sx_tave->FindBin(40));

  //sx_tave->GetXaxis()->SetTitle("S_{X} (MeV)"); 
  //sx_tave->GetYaxis()->SetTitle("#it{d#sigma/dE_{p}d#Omega_{p}d#Omega_{X}dS_{X}} (#it{#mu}b/MeV#upoint str^{2}  per 200 keV)");
  
  sx_tave->SetMinimum(ymin);
  sx_tave->SetMaximum(ymax);

  sx_tave->SetLabelSize(0.06,"y");
  
  sx_tave->SetStats(0);
  sx_tave0->SetStats(0);
  sx_tave->Draw();
  sx_tave0->Draw("same");
  
  Double_t Sh=18.830; // 3/2+                                                                                                                              
  Double_t E1=1409.84/1000.0; //1/2+                                                                                                                         
  Double_t E2=2217.00/1000.0; //7/2+
  Double_t E3=2796.15/1000.0; //5/2+  
  Double_t E4=3170.0/1000.0; //5/2+


  Double_t y0=0.12;
  TArrow a0(Sh,y0,Sh,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(Sh,y0+0.06,Form("#scale[%f]{gnd (3/2^{+})}",scale*0.75));

  Double_t y1=0.72;
  TArrow a1(Sh+E1,y1,Sh+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(Sh+E1-1.0,y1+0.06,Form("#scale[%f]{1.40 MeV}",scale*0.75));
  t1.DrawLatex(Sh+E1+0.5,y1+0.06,Form("#scale[%f]{(1/2^{+})}",scale*0.75));

  Double_t y2=0.10;
  TArrow a2(Sh+E2,y2,Sh+E2,y2+0.05,0.01,"<|");
  //a2.Draw();
  TLatex t2;
  t2.SetTextAlign(12);
  t2.SetTextAngle(90);
  //t2.DrawLatex(Sh+E2+0.25,y2+0.07,"#scale[1.2]{7/2^{+}}");

  Double_t y3=0.10;
  TArrow a3(Sh+E3,y3,Sh+E3,y3+0.05,0.01,"<|");
  //a3.Draw();
  TLatex t3;
  t3.SetTextAlign(12);
  t3.SetTextAngle(90);
  //t3.DrawLatex(Sh+E3+1.0,y3+0.07,"#scale[1.2]{5/2^{+}}");

  Double_t y4=0.10;
  TArrow a4(Sh+E4,y3,Sh+E4,y4+0.05,0.01,"<|");
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

  Double_t y0_16O=0.18;
  TArrow a0_16O(St_16O,y0_16O,St_16O,y0_16O+0.05,0.01,"<|");
  a0_16O.Draw();
  t_16O.DrawLatex(St_16O,y0_16O+0.06,Form("#scale[%f]{^{13}C}",0.75*scale));
  Double_t y1_16O=0.3;
  TArrow a1_16O(St_16O+E1_16O,y1_16O,St_16O+E1_16O,y1_16O+0.05,0.01,"<|");
  a1_16O.Draw();
  t_16O.DrawLatex(St_16O+E1_16O+1.5,y1_16O+0.06,Form("#scale[%f]{^{13}C}",0.75*scale));  

  
  //TF1 *f_40Ca = new TF1("f_40Ca","([0]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[1])/[8],2))+([2]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[3])/[8],2))+([4]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[5])/[8],2))+([6]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[7])/[8],2))",-1000,1000);
  TF1 *f_40Ca = new TF1("f_40Ca","([0]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[1])/[10],2))+([2]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[3])/[10],2))+([4]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[5])/[10],2))+([6]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[7])/[10],2))+([8]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[9])/[10],2))",-1000,1000);

  f_40Ca->SetParLimits(0,0.0,1.0);
  f_40Ca->SetParLimits(2,0.0,1.0);
  f_40Ca->SetParLimits(4,0.0,1.0);
  f_40Ca->SetParLimits(8,0.0,1.0);
  /*
  f_40Ca->SetParLimits(5,20.95,21.05);
  f_40Ca->SetParLimits(7,21.5,21.7);
  f_40Ca->SetParLimits(9,21.9,22.1);
  */


  
  f_40Ca->SetParameters(0.05,Sh+0.2,
			0.2,Sh+E1,
			0.01,Sh+E2,
			0.01,Sh+E3,
			0.01,Sh+E4,		   			
			0.5);
  
  f_40Ca->FixParameter(5,Sh+E2+0.25);
  f_40Ca->FixParameter(7,Sh+E3+0.25);
  f_40Ca->FixParameter(9,Sh+E4+0.25);

  sx_tave->Fit("f_40Ca","E","",18.0,22.2);


  int Nbin=sx_tave->GetXaxis()->GetNbins();
  double tdx=f_40Ca->GetParameter(2)/((double) 50.0/Nbin);
  double tdx_err=f_40Ca->GetParError(2)/((double) 50.0/Nbin);
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{40}Ca(#it{p,p}^{3}He)}",scale*1.0));
  title.DrawLatex(.65,.725,Form("#scale[%f]{#it{S}_{^{3}He}=18.830 MeV}",scale*0.8));
  title.DrawLatex(.60,.65,Form("#scale[%f]{TDX = %8.3f #pm %8.3f}",scale*0.8,tdx,tdx_err));
  
}
