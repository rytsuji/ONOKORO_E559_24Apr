{
  double scale=1/(1.0-0.05/(0.21250000+0.05));
  //
  //TFile *file_44Ca = TFile::Open("macro/ppx/output_sx/pph_44Ca_tave.root");
  TFile *file_44Ca = TFile::Open("output/ppx/pph_44Ca.tra_ave.root ");  

  Double_t ymin=-0.0499;
  Double_t ymax=0.9999;
  
  //sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(15),sx_tave->FindBin(40));
  
  sx_tave->SetMinimum(ymin);
  sx_tave->SetMaximum(ymax);

  sx_tave->SetLabelSize(0.06,"y");
  
  sx_tave->SetStats(0);
  sx_tave0->SetStats(0);
  sx_tave->Draw();
  sx_tave0->Draw("same");
  
  Double_t Sh=23.332; // 7/2-                                                                                                                              
  Double_t E1=1033.94/1000.0; //3/2+                                                                                                                         
  Double_t E2=1867.99/1000.0; //1/2+
  Double_t E3=2891/1000.0; //9/2+  

  /*
  Double_t y0=0.08;
  TArrow a0(Sh,y0,Sh,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(Sh,y0+0.06,"#scale[1.2]{gnd (7/2^{-})}");
  */
  
  Double_t y1=0.1;
  TArrow a1(Sh+E1,y1,Sh+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(Sh+E1-0.5,y1+0.06,Form("#scale[%f]{3/2^{+}}",0.75*scale));

  Double_t y2=0.450;
  TArrow a2(Sh+E2,y2,Sh+E2,y2+0.05,0.01,"<|");
  a2.Draw();
  TLatex t2;
  t2.SetTextAlign(12);
  t2.SetTextAngle(90);
  t2.DrawLatex(Sh+E2+0.25,y2+0.07,Form("#scale[%f]{1.86 MeV (1/2^{+})}",0.75*scale));

  Double_t y3=0.10;
  TArrow a3(Sh+E3,y3,Sh+E3,y3+0.05,0.01,"<|");
  //a3.Draw();
  TLatex t3;
  t3.SetTextAlign(12);
  t3.SetTextAngle(90);
  //t3.DrawLatex(Sh+E3,y3+0.07,"#scale[1.2]{9/2^{+}}");


  Double_t St_16O=22.793;
  Double_t E1_16O=3089.443/1000.;
  TLatex t_16O;
  t_16O.SetTextAlign(12);
  t_16O.SetTextAngle(90);

  Double_t y0_16O=0.18;
  TArrow a0_16O(St_16O,y0_16O,St_16O,y0_16O+0.05,0.01,"<|");
  a0_16O.Draw();
  t_16O.DrawLatex(St_16O,y0_16O+0.06,Form("#scale[%f]{^{13}C}",0.75*scale));
  Double_t y1_16O=0.45;
  TArrow a1_16O(St_16O+E1_16O,y1_16O,St_16O+E1_16O,y1_16O+0.05,0.01,"<|");
  a1_16O.Draw();
  t_16O.DrawLatex(St_16O+E1_16O+1.5,y1_16O+0.06,Form("#scale[%f]{^{13}C}",0.75*scale));

  //Double_t E2_16O=3.547;
  //Double_t y2_16O=0.45;
  //TArrow a2_16O(St_16O+E2_16O,y2_16O,St_16O+E2_16O,y2_16O+0.05,0.01,"<|");
  //a2_16O.Draw();
  //t_16O.DrawLatex(St_16O+E2_16O,y2_16O+0.06,Form("#scale[%f]{^{13}C}",0.75*scale));
  

   TF1 *f_44Ca = new TF1("f_44Ca","([0]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[1])/[8],2))+([2]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[3])/[8],2))+([4]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[5])/[8],2))+([6]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[7])/[8],2))",-1000,1000);
   
  f_44Ca->SetParLimits(1,22.6,22.8);
  f_44Ca->SetParLimits(3,23.2,23.5);
  f_44Ca->SetParLimits(5,25.0,25.6);
  f_44Ca->SetParLimits(7,26.2,26.4);

  f_44Ca->SetParLimits(0,0.0,1.0);
  f_44Ca->SetParLimits(2,0.0,1.0);
  f_44Ca->SetParLimits(4,0.0,1.0);
  f_44Ca->SetParLimits(6,0.0,1.0);    
  

  
  f_44Ca->SetParameters(0.1,22.5,
			0.05,24.7,
			0.3,25.5,
			0.3,26.5,
			0.4);
 
  sx_tave->Fit("f_44Ca","E","",22.0,26.8);  

  int Nbin=sx_tave->GetXaxis()->GetNbins();
  double tdx=f_44Ca->GetParameter(4)/((double) 50.0/Nbin);
  double tdx_err=f_44Ca->GetParError(4)/((double) 50.0/Nbin);
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,0.8,Form("#scale[%f]{^{44}Ca(#it{p,p}^{3}He)}",1.0*scale));
  title.DrawLatex(.65,0.725,Form("#scale[%f]{#it{S}_{^{3}He}=23.3322 MeV}",0.8*scale));
  title.DrawLatex(.60,.65,Form("#scale[%f]{TDX = %8.3f #pm %8.3f}",0.8*scale,tdx,tdx_err));


  
  
  /*
  TF1 *f_44Ca = new TF1("f_44Ca","([0]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[1])/[8],2))+([2]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[3])/[8],2))+([4]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[5])/[8],2))+([6]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[7])/[8],2))",-1000,1000);
 
  f_44Ca->SetParLimits(0,0.0,1.0);
  f_44Ca->SetParLimits(2,0.0,1.0);
  f_44Ca->SetParLimits(4,0.0,1.0);
  f_44Ca->SetParLimits(6,0.0,1.0);

  f_44Ca->SetParameters(0.05,Sh+E1,
			0.1,Sh+E2,
			0.05,Sh+E3-0.5,
			0.05,Sh+E3,		   			
			0.5);
  

  sx_tave->Fit("f_44Ca","E","",23.0,27.0);
  */

  //TF1 *f_44Ca = new TF1("f_44Ca","([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",-1000,1000);

 
  //TF1 *f_44Ca = new TF1("f_44Ca","([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",-1000,1000);
  
  //f_44Ca->SetParLimits(0,0.0,1.0);
  //f_44Ca->SetParLimits(2,0.0,1.0);
  ///f_44Ca->SetParLimits(4,0.0,1.0);
  //f_44Ca->SetParLimits(6,0.0,1.0);
  /*
  f_44Ca->SetParameters(0.03,24.0,
			1.31492e-01,2.50175e+01,
			2.22895e-02,2.70577e+01,
			1.60754e-01,2.61575e+01,
			3.28856e-01);
  */


}

