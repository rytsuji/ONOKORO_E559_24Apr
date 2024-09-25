{
  //
  double scale=1/(1.0-0.05/(0.21250000+0.05));
  //TFile *file_44Ca = TFile::Open("macro/ppx/output_sx/ppt_44Ca_tave.root");
  TFile *file_44Ca = TFile::Open("output/ppx/ppt_44Ca.tra_ave.root ");

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
  
  Double_t St=20.859;
  Double_t E1=980.476/1000.0;
  Double_t E2=1559.903/1000.0;
  Double_t E3=1593.107/1000.0;

  Double_t y0=0.075;
  TArrow a0(St,y0,St,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St-0.5,y0+0.07,Form("#scale[%f]{gnd (3/2^{+})}",scale*0.75));
  Double_t y1=0.28;
  TArrow a1(St+E1,y1,St+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St+E1,y1+0.07,Form("#scale[%f]{0.98 MeV (1/2^{+})}",0.75*scale));
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

  Double_t y0_16O=0.18;
  TArrow a0_16O(St_16O,y0_16O,St_16O,y0_16O+0.05,0.01,"<|");
  a0_16O.Draw();
  t_16O.DrawLatex(St_16O,y0_16O+0.06,Form("#scale[%f]{^{13}N}",0.75*scale));
  Double_t y1_16O=0.2;
  TArrow a1_16O(St_16O+E1_16O,y1_16O,St_16O+E1_16O,y1_16O+0.05,0.01,"<|");
  a1_16O.Draw();
  t_16O.DrawLatex(St_16O+E1_16O,y1_16O+0.06,Form("#scale[%f]{^{13}N}",0.75*scale));

  Double_t E2_16O=3.547;
  Double_t y2_16O=0.45;
  TArrow a2_16O(St_16O+E2_16O,y2_16O,St_16O+E2_16O,y2_16O+0.05,0.01,"<|");                                                                                       
  a2_16O.Draw();                                                                                                                                                 
  t_16O.DrawLatex(St_16O+E2_16O,y2_16O+0.06,Form("#scale[%f]{^{13}N}",0.75*scale));
  
  TF1 *f_44Ca = new TF1("f_44Ca","([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",-600,600);

  //TF1 *f_44Ca = new TF1("f_44Ca","([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",-600,600);

  f_44Ca->SetParameters(0.01,St,
			0.05,St+E1,
			0.02,St+E2,
			0.2);
  
  //f_44Ca->SetParameters(0.05,St+E1,
  //0.02,St+E2,
  //0.2);
  sx_tave->Fit("f_44Ca","E","",20.0,22.8);
  int Nbin=sx_tave->GetXaxis()->GetNbins();
  double tdx=f_44Ca->GetParameter(2)/((double) 50.0/Nbin);
  double tdx_err=f_44Ca->GetParError(2)/((double) 50.0/Nbin);
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{44}Ca#it{(p,pt)}}",1.0*scale));
  title.DrawLatex(.65,.725,Form("#scale[%f]{#it{S_{t}}=20.859 MeV}",0.8*scale));
  title.DrawLatex(.60,.65,Form("#scale[%f]{TDX = %8.3f #pm %8.3f}",0.8*scale,tdx,tdx_err));

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
