

{
  //
  double scale=1/(1.0-0.05/(0.21250000+0.05));
  //TFile *file_42Ca = TFile::Open("macro/ppx/output_sx/ppt_42Ca_tave.root");
  TFile *file_42Ca = TFile::Open("output/ppx/ppt_42Ca.tra_ave.root ");
  
  Double_t ymin=-0.0499;
  Double_t ymax=0.8499;
  
  sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(10),sx_tave->FindBin(45));
  
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
  t0.DrawLatex(St,y0+0.06,Form("#scale[%f]{gnd (3/2^{+})}",0.75*scale));

  Double_t y1=0.32;
  TArrow a1(St+E1,y1,St+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St+E1,y1+0.05,Form("#scale[%f]{2.52 MeV (1/2^{+})}",0.75*scale));
  //t1.DrawLatex(St+E1+0.4,y1+0.04,"#scale[1.2]{  (1/2^{+})}");


  /*
  Double_t y2=0.07;
  TArrow a2(St+E2,y2,St+E2,y2+0.05,0.01,"<|");
  a2.Draw();
  TLatex t2;
  t2.SetTextAlign(11);                                                                                                                   
  t2.DrawLatex(St+E2,y2+0.07,"#scale[0.75]{#frac{5}{2}^{+}, #frac{7}{2}^{+}}");  
  */

  Double_t St_16O=25.032;
  Double_t E1_16O=2.3649;;
  TLatex t_16O;
  t_16O.SetTextAlign(12);
  t_16O.SetTextAngle(90);

  Double_t y0_16O=0.42;
  TArrow a0_16O(St_16O,y0_16O,St_16O,y0_16O+0.05,0.01,"<|");
  a0_16O.Draw();
  t_16O.DrawLatex(St_16O,y0_16O+0.06,Form("#scale[%f]{^{13}N}",0.75*scale));
  Double_t y1_16O=0.22;
  TArrow a1_16O(St_16O+E1_16O,y1_16O,St_16O+E1_16O,y1_16O+0.05,0.01,"<|");
  a1_16O.Draw();
  t_16O.DrawLatex(St_16O+E1_16O,y1_16O+0.06,Form("#scale[%f]{^{13}N}",0.75));

  Double_t E2_16O=3.547;
  Double_t y2_16O=0.65;
  TArrow a2_16O(St_16O+E2_16O,y2_16O,St_16O+E2_16O,y2_16O+0.05,0.01,"<|");                                                                                       
  a2_16O.Draw();                                                                                                                                                 
  t_16O.DrawLatex(St_16O+E2_16O,y2_16O+0.06,Form("#scale[%f]{^{13}N}",0.75*scale));

  //gROOT->LoadMacro("macro/function/def_4gaus.C");
  TF1 *f_42Ca=new TF1("f_42Ca","gausn",-100,100);
  sx_tave->Fit("f_42Ca","E","",20.5,24.0);

  int Nbin=sx_tave->GetXaxis()->GetNbins();
  double tdx=f_42Ca->GetParameter(0)/((double) 50.0/Nbin);
  double tdx_err=f_42Ca->GetParError(0)/((double) 50.0/Nbin);

  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{42}Ca#it{(p,pt)}}",1.0*scale));
  title.DrawLatex(.65,.725,Form("#scale[%f]{#it{S_{t}}=19.690 MeV}",0.8*scale));
  title.DrawLatex(.60,.65,Form("#scale[%f]{TDX = %8.3f #pm %8.3f}",0.8*scale,tdx,tdx_err))

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
