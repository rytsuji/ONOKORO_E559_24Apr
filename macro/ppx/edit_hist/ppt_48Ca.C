
{
 
  
  double offset=0.0;
  //
  //TFile *file_48Ca = TFile::Open("macro/ppx/output_sx/ppt_48Ca_tave.root");
  TFile *file_48Ca = TFile::Open("output/ppx/ppt_48Ca.tra_ave.root ");

  Double_t ymin=-0.0499;
  Double_t ymax=0.8499;

  sx_tave->GetXaxis()->SetRange(sx_tave->FindBin(10),sx_tave->FindBin(45));

  sx_tave->SetLabelSize(0.06*(1.0-offset),"xy");
  
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


  Double_t y0=0.10;
  TArrow a0(St,y0,St,y0+0.05,0.01,"<|");
  a0.Draw(); 
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St-1.0,y0+0.06,Form("#scale[%e]{gnd (3/2^{+})}",0.75));
  Double_t y1=0.20;
  TArrow a1(St+E1,y1,St+E1,y1+0.05,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St+E1+0.5,y1+0.06,Form("#scale[%e]{0.47 MeV (1/2^{+})}",0.75));

  Double_t St_16O=25.032;
  Double_t E1_16O=2.3649;
  TLatex t_16O;
  t_16O.SetTextAlign(12);
  t_16O.SetTextAngle(90);

  Double_t y0_16O=0.25;
  TArrow a0_16O(St_16O,y0_16O,St_16O,y0_16O+0.05,0.01,"<|");
  a0_16O.Draw();
  t_16O.DrawLatex(St_16O,y0_16O+0.06,"#scale[0.75]{^{13}N}");
  Double_t y1_16O=0.25;
  TArrow a1_16O(St_16O+E1_16O,y1_16O,St_16O+E1_16O,y1_16O+0.05,0.01,"<|");
  a1_16O.Draw();
  t_16O.DrawLatex(St_16O+E1_16O,y1_16O+0.06,"#scale[0.75]{^{13}N}");

  Double_t E2_16O=3.547;  
  Double_t y2_16O=0.6;
  TArrow a2_16O(St_16O+E2_16O,y2_16O,St_16O+E2_16O,y2_16O+0.05,0.01,"<|");
  a2_16O.Draw();
  t_16O.DrawLatex(St_16O+E2_16O,y2_16O+0.06,"#scale[0.75]{^{13}N}");  
  //gROOT->LoadMacro("macro/function/def_3gaus.C");
  //TF1 *f_48Ca = new TF1("f_48Ca","([0]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[1])/[6],2))+([2]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[3])/[6],2))+([4]/sqrt(2.*TMath::Pi()*[6]*[6]))*exp(-0.5*pow((x-[5])/[6],2))",-600,600);

  TF1 *f_48Ca = new TF1("f_48Ca","([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",-600,600);

  //TF1 *f_48Ca=new TF1("f_48Ca","gausn",-100,100);
  
  f_48Ca->SetParameters(0.005,St-0.2,
			0.02,St+E1,
			//0.01,St+E2,
			0.2);
  sx_tave->Fit("f_48Ca","E","",21.5,23.5);
  
  int Nbin=sx_tave->GetXaxis()->GetNbins();
  double tdx=f_48Ca->GetParameter(2)/((double) 50.0/Nbin);
  double tdx_err=f_48Ca->GetParError(2)/((double) 50.0/Nbin);
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,offset+0.8,Form("#scale[%e]{^{48}Ca#it{(p,pt)}}",1.0));
  title.DrawLatex(.65,offset+0.725,Form("#scale[%e]{#it{S_{t}}=22.559 MeV}",0.8));
  title.DrawLatex(.60,.65,Form("#scale[0.8]{TDX = %8.3f #pm %8.3f}",tdx,tdx_err))
  
  

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
