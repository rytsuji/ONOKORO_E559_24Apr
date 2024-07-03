{
  //
  TFile *file_42Ca = TFile::Open("macro/ppx/output_sx/pph_42Ca_tave.root");
  

  Double_t ymin=-0.0499;
  Double_t ymax=0.4999;
  
  sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(15),sx_tave->FindBin(40));
  
  sx_tave->SetMinimum(ymin);
  sx_tave->SetMaximum(ymax);

  sx_tave->SetLabelSize(0.06,"y");
  
  sx_tave->SetStats(0);
  sx_tave0->SetStats(0);
  sx_tave->Draw();
  sx_tave0->Draw("same");
  
  Double_t Sh=20.236; // 7/2-                                                                                                                              
  Double_t E1=1517.540/1000.0; //3/2+                                                                                                                         
  Double_t E2=2358.284/1000.0; //1/2+
  Double_t E3=2503.418/1000.0; //5/2+  
  Double_t E4=2829.934/1000.0; //1/2+


  Double_t y0=0.02;
  TArrow a0(Sh,y0,Sh,y0+0.05,0.01,"<|");
  //a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  //t0.DrawLatex(Sh,y0+0.06,"#scale[1.2]{gnd (7/2^{-})}");

  Double_t y1=0.1;
  TArrow a1(Sh+E1,y1,Sh+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(Sh+E1,y1+0.06,"#scale[1.2]{3/2^{+}}");

  Double_t y2=0.3;
  TArrow a2(Sh+E2,y2,Sh+E2,y2+0.05,0.01,"<|");
  a2.Draw();
  TLatex t2;
  t2.SetTextAlign(12);
  t2.SetTextAngle(90);
  t2.DrawLatex(Sh+E2-0.4,y2+0.05,"#scale[1.2]{2.35 MeV}");
  t2.DrawLatex(Sh+E2+0.4,y2+0.05,"#scale[1.2]{(1/2^{+})}");  

  Double_t y3=0.25;
  TArrow a3(Sh+E3,0.025,Sh+E3,0.075,0.01,"|>");
  a3.Draw();
  TLatex t3;
  t3.SetTextAlign(12);
  t3.SetTextAngle(90);
  t3.DrawLatex(Sh+E3-0.25,-0.04,"#scale[1.2]{5/2^{+}}");

  Double_t y4=0.10;
  TArrow a4(Sh+E4,0.025,Sh+E4,0.075,0.01,"|>");
  a4.Draw();
  TLatex t4;
  t4.SetTextAlign(12);
  t4.SetTextAngle(90);
  t4.DrawLatex(Sh+E4+0.25,-0.04,"#scale[1.2]{1/2^{+}}");


  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,"#scale[1.5]{^{42}Ca(#it{p,p}^{3}He)}");
  title.DrawLatex(.65,.7,"#scale[1.2]{#it{S}_{^{3}He}=20.236 MeV}");

  //TF1 *f_40Ca = new TF1("f_40Ca","([0]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[1])/[8],2))+([2]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[3])/[8],2))+([4]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[5])/[8],2))+([6]/sqrt(2.*TMath::Pi()*[8]*[8]))*exp(-0.5*pow((x-[7])/[8],2))",-1000,1000);
  TF1 *f_40Ca = new TF1("f_40Ca","([0]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[1])/[10],2))+([2]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[3])/[10],2))+([4]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[5])/[8],2))+([6]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[7])/[10],2))+([8]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[9])/[10],2))",-1000,1000);

  f_40Ca->SetParLimits(0,0.0,1.0);
  f_40Ca->SetParLimits(2,0.0,1.0);
  f_40Ca->SetParLimits(4,0.0,1.0);
  f_40Ca->SetParLimits(8,0.0,1.0);
  /*
  f_40Ca->SetParLimits(5,20.95,21.05);
  f_40Ca->SetParLimits(7,21.5,21.7);
  f_40Ca->SetParLimits(9,21.9,22.1);
  */


  
  f_40Ca->SetParameters(0.05,Sh,
			0.2,Sh+E1,
			0.02,Sh+E2,
			0.02,Sh+E3,
			0.02,Sh+E4,		   			
			0.5);
  
  f_40Ca->FixParameter(5,Sh+E2);
  f_40Ca->FixParameter(7,Sh+E3);
  f_40Ca->FixParameter(9,Sh+E4);

  //sx_tave->Fit("f_40Ca","E","",18.0,22.2);
  

}
