
{
  double offset=0.0;
  //
  TFile *file_48Ca = TFile::Open("macro/ppx/output_sx/pph_48Ca_tave.root");
  

  Double_t ymin=-0.0499;
  Double_t ymax=0.2499;

  sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(15),sx_tave->FindBin(40));
  
  sx_tave->SetMinimum(ymin);
  sx_tave->SetMaximum(ymax);


  sx_tave->SetLabelSize(0.06*(1-offset),"xy");  

  sx_tave->SetStats(0);
  sx_tave0->SetStats(0);
  sx_tave->Draw();
  sx_tave0->Draw("same");
  
  Double_t Sh=29.385; // 7/2-                                                                                                                              
  Double_t E1=1.660;
  Double_t E2=2.420;
  Double_t E3=3.230;


  Double_t y0=0.02;
  TArrow a0(Sh,y0,Sh,y0+0.05,0.01,"<|");
  //a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  //t0.DrawLatex(Sh,y0+0.06,"#scale[1.2]{gnd (7/2^{-})}");

  Double_t y1=0.06;
  TArrow a1(Sh+E1,y1,Sh+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(Sh+E1,y1+0.06,Form("#scale[%e]]{3/2^{+}}",1.2*(1-offset)));

  Double_t y2=0.03;
  //dE2=-0.5;
  //E2+=dE2;
  TArrow a2(Sh+E2,y2,Sh+E2,y2+0.05,0.01,"<|");
  a2.Draw();
  TLatex t2;
  t2.SetTextAlign(12);
  t2.SetTextAngle(90);
  t2.DrawLatex(Sh+E2,y2+0.07,Form("#scale[%e]{2.42 MeV (1/2^{+}?)}",1.2*(1-offset)));

  Double_t y3=0.03;
  TArrow a3(Sh+E3,y3,Sh+E3,y3+0.05,0.01,"<|");
  //a3.Draw();
  TLatex t3;
  t3.SetTextAlign(12);
  t3.SetTextAngle(90);
  //t3.DrawLatex(Sh+E3,y3+0.07,"#scale[1.2]{5/2^{+}}");


  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);

  title.DrawLatex(.65,offset+0.8*(1-offset),Form("#scale[%e]{^{48}Ca(#it{p,p}^{3}He)}",1.5*(1.0-offset)));
  title.DrawLatex(.65,offset+0.7*(1-offset),Form("#scale[%e]{#it{S}_{^{3}He}=29.385 MeV}",1.2*(1.0-offset)));

  /*
  TF1 *f_48Ca = new TF1("f_48Ca","([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",-1000,1000);

  f_48Ca->SetParLimits(0,0.0,1.0);
  f_48Ca->SetParLimits(2,0.0,1.0);

  f_48Ca->SetParameters(0.03,30.3,
			0.03,31.0,
			0.3);
  
  sx_tave->Fit("f_48Ca","E","",29.5,32.2);
  */

    TF1 *f_48Ca = new TF1("f_48Ca","([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",-1000,1000);

  f_48Ca->SetParLimits(0,0.0,1.0);
  f_48Ca->SetParLimits(2,0.0,1.0);
  f_48Ca->SetParLimits(4,0.0,1.0);

  f_48Ca->SetParameters(0.03,30.5,
			0.03,31.0,			
			0.03,31.8,
			0.3);
  
  sx_tave->Fit("f_48Ca","E","",29.5,32.2);

}
