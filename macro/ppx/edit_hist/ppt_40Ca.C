{
  //
  TFile *file_40Ca = TFile::Open("macro/ppx/output_sx/ppt_40Ca_tave.root");
  

  Double_t ymin=-0.0499;
  Double_t ymax=0.3999;
  
  sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(18),sx_tave->FindBin(38));
  
  sx_tave->SetMinimum(ymin);
  sx_tave->SetMaximum(ymax);

  sx_tave->SetLabelSize(0.06,"y");
  
  sx_tave->SetStats(0);
  sx_tave0->SetStats(0);
  sx_tave->Draw();
  sx_tave0->Draw("same");
  
  Double_t St=24.996; // 3/2+                                                                                                                              
  Double_t E1=1370.85/1000.0; //1/2+                                                                                                                         
  Double_t E2=2285.24/1000.0; //5/2+, 7/2+                                                                                                                   
  Double_t E3=2750.22/1000.0; //5/2+                                                                                                                         
  Double_t E4=3239.5/1000.0; //5/2+

  Double_t y0=0.10;
  TArrow a0(St,y0,St,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St,y0+0.06,"#scale[1.2]{gnd} (3/2^{+})");

  Double_t y1=0.24;
  TArrow a1(St+E1,y1,St+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St+E1-0.4,y1+0.04,"#scale[1.2]{1.37 MeV}");
  t1.DrawLatex(St+E1+0.4,y1+0.04,"#scale[1.2]{  (1/2^{+})}");
  /*
  Double_t y2=0.06;
  TArrow a2(St+E2,y2,St+E2,y2+0.05,0.01,"<|");
  a2.Draw();
  TLatex t2;
  t2.SetTextAlign(12);
  t2.SetTextAngle(90);
  t2.DrawLatex(St+E2-0.2,y2+0.06,"#scale[1.0]{3.23 MeV (5,7/2^{+})}");

  Double_t y3=0.12;
  TArrow a3(St+E3,y3,St+E3,y3+0.05,0.01,"<|");
  a3.Draw();
  TLatex t3;
  t3.SetTextAlign(12);
  t3.SetTextAngle(90);
  t3.DrawLatex(St+E3+0.2,y3+0.06,"#scale[1.0]{2.28 MeV (5/2^{+})}");
  */
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,"#scale[1.5]{^{40}Ca#it{(p,pt)}}");
  title.DrawLatex(.65,.7,"#scale[1.2]{#it{S_{t}}=24.996 MeV}");
  


  TF1 *f_40Ca = new TF1("f_40Ca","([0]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[1])/[8],2))+([2]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[3])/[8],2))+([4]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[5])/[8],2))+([6]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[7])/[8],2))",-1000,1000);

  //gROOT->LoadMacro("macro/function/def_4gaus.C");
  //TF1 *f_40Ca = new TF1("f_40Ca","f",-1000,1000);
  f_40Ca->SetParameters(0.05,St,
			0.10,St+E1,
			0.03,St+E2,
			0.05,27.8,		   
			0.2);
  sx_tave->Fit("f_40Ca","E","",24,28.25);

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
