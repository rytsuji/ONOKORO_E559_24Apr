
{
  double offset=0.05/(0.21250000+0.05);
  //
  TFile *file_48Ca = TFile::Open("macro/ppx/output_sx/ppt_48Ca_tave.root");
  

  Double_t ymin=-0.0499;
  Double_t ymax=0.3999;

  sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(18),sx_tave->FindBin(38));

  sx_tave->SetLabelSize(0.06*(1-offset),"xy");
  
  sx_tave->SetMinimum(ymin);
  sx_tave->SetMaximum(ymax);

  sx_tave->SetStats(0);
  sx_tave0->SetStats(0);
  sx_tave->Draw();
  sx_tave0->Draw("same");
  Double_t St=22.559;
  Double_t E1=474.45/1000.0;
  Double_t E2=980.476/1000.0;
  Double_t E3=1424.3/1000.0;
  Double_t E4=1639.15/1000.0;
  Double_t E5=2188.22/1000.0;
  Double_t E6=2747.9/1000.0;


  Double_t y0=0.1;
  TArrow a0(St,y0,St,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St-0.4,y0+0.06,Form("#scale[%e]{gnd (3/2^{+})}",1.2*(1.0-offset)));
  Double_t y1=0.11;
  TArrow a1(St+E1,y1,St+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St+E1+0.4,y1+0.06,Form("#scale[%e]{0.47 MeV (1/2^{+})}",1.2*(1.0-offset)));

  /*
  Double_t y2=0.07;
  TArrow a2(St+E2,y2,St+E2,y2+0.05,0.01,"<|");
  a2.Draw();
  TLatex t2;
  t2.SetTextAlign(11);                                                                                                                   
  t2.DrawLatex(St+E2,y2+0.07,"#scale[0.75]{#frac{5}{2}^{+}, #frac{7}{2}^{+}}");  
  */

  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,offset+0.8*(1-offset),Form("#scale[%e]{^{48}Ca#it{(p,pt)}}",1.5*(1.0-offset)));
  title.DrawLatex(.65,offset+0.7*(1-offset),Form("#scale[%e]{#it{S_{t}}=22.559 MeV}",1.2*(1.0-offset)));
  
  //gROOT->LoadMacro("macro/function/def_3gaus.C");
  TF1 *f_48Ca = new TF1("f_48Ca","([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",-600,600);
  f_48Ca->SetParameters(0.01,St,
		   0.05,St+E1,
		   0.01,St+E2,
		   0.2);
  sx_tave->Fit("f_48Ca","E","",22,23.5);



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
