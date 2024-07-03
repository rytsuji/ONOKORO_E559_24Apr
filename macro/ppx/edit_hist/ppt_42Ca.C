{
  //
  TFile *file_42Ca = TFile::Open("macro/ppx/output_sx/ppt_42Ca_tave.root");
  
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
  
  Double_t St=19.690;
  Double_t E1=2522.75/1000.0;
  Double_t E2=3938.9/1000.0;
  Double_t E3=4095.6/1000.0;

  Double_t y0=0.07;
  TArrow a0(St,y0,St,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St,y0+0.06,"#scale[1.2]{gnd (3/2^{+})}");
  Double_t y1=0.18;
  TArrow a1(St+E1,y1,St+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St+E1-0.4,y1+0.04,"#scale[1.2]{2.52 MeV}");
  t1.DrawLatex(St+E1+0.4,y1+0.04,"#scale[1.2]{  (1/2^{+})}");


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
  title.DrawLatex(.65,.8,"#scale[1.5]{^{42}Ca#it{(p,pt)}}");
  title.DrawLatex(.65,.7,"#scale[1.2]{#it{S_{t}}=19.690 MeV}");
  //gROOT->LoadMacro("macro/function/def_4gaus.C");
  TF1 *f_42Ca=new TF1("f_42Ca","gausn",-100,100);
  sx_tave->Fit("f_42Ca","E","",20.5,24.0);



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
