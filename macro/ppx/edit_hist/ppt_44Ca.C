{
  //
  TFile *file_44Ca = TFile::Open("macro/ppx/output_sx/ppt_44Ca_tave.root");
  

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
  
  Double_t St=20.859;
  Double_t E1=980.476/1000.0;
  Double_t E2=1559.903/1000.0;
  Double_t E3=1593.107/1000.0;

  Double_t y0=0.1;
  TArrow a0(St,y0,St,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St,y0+0.07,"#scale[1.2]{gnd (3/2^{+})}");
  Double_t y1=0.12;
  TArrow a1(St+E1,y1,St+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St+E1,y1+0.07,"#scale[1.2]{0.98 MeV (1/2^{+})}");
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
  title.DrawLatex(.65,.8,"#scale[1.5]{^{44}Ca#it{(p,pt)}}");
  title.DrawLatex(.65,.7,"#scale[1.2]{#it{S_{t}}=20.859 MeV}");
  //gROOT->LoadMacro("macro/function/def_3gaus.C");
  TF1 *f_44Ca = new TF1("f_44Ca","([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",-600,600);

  f_44Ca->SetParameters(0.05,St,
		   0.05,St+E1,
		   0.02,St+E2,
		   0.2);
  sx_tave->Fit("f_44Ca","E","",19,23);



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
