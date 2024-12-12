{
  int bin=2;
  double scale=1.0;
 
  //double scale_ppt=1.0;
  //double scale_ppt=0.625602/0.353068;
  double scale_ppt=1.46;
  double xmin=-1;
  double xmax=12;
  double ymin=-0.075; 
  double ymax=0.15; 
  //double ymax=0.8;

  TLine *lz = new TLine(xmin,0,xmax+2,0);
  lz->SetLineStyle(2);
  lz->SetLineWidth(3);
  
  TFile *file0 = TFile::Open("output/calib_pid/hist_ex/pph_40Ca.raw.root");   
  TCanvas *c1=new TCanvas("c1","",800,600);
  h_40Ca->Rebin(bin);
  h_40Ca0->Rebin(bin);
  h_40Ca->SetMinimum(ymin);
  h_40Ca->SetMaximum(ymax);  
  h_40Ca->GetXaxis()->SetRange(h_40Ca->FindBin(xmin),h_40Ca->FindBin(xmax));
  h_40Ca->SetStats(0);
  h_40Ca->Draw("E1");
  h_40Ca0->Draw("same");

  TFile *file1 = TFile::Open("output/calib_pid/hist_ex/ppt_40Ca.raw.root"); 
  h_40Ca->Scale(scale_ppt);
  h_40Ca0->Scale(scale_ppt);
  h_40Ca->Rebin(bin);
  h_40Ca0->Rebin(bin);
  h_40Ca0->Sumw2(0);
  h_40Ca->SetLineColor(2);
  h_40Ca->SetMarkerColor(2);  
  h_40Ca0->SetLineColor(2);
  h_40Ca->Draw("same E1");
  h_40Ca0->Draw("same");

  //lz->Draw("same");
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{40}Ca}",1.0*scale));


  TLatex t_ppt;
  t_ppt.SetTextColor(2);
  t_ppt.SetTextAlign(12);
  t_ppt.SetTextAngle(90);

  Double_t y0_ppt=0.04;
  Double_t e0_ppt=0.0;
  TArrow a0_ppt(e0_ppt,y0_ppt,e0_ppt,y0_ppt+0.05/5,0.01,"<|");
  a0_ppt.SetLineColor(2);
  a0_ppt.SetFillColor(2);  
  a0_ppt.Draw();
  t_ppt.DrawLatex(e0_ppt,y0_ppt+0.06/5,Form("#scale[%f]{3/2^{+} (g.s.)}",scale*0.75));

  Double_t y1_ppt=0.10;
  Double_t e1_ppt=1.370;
  TArrow a1_ppt(e1_ppt,y1_ppt,e1_ppt,y1_ppt+0.05/5,0.01,"<|");
  a1_ppt.SetLineColor(2);
  a1_ppt.SetFillColor(2);  
  a1_ppt.Draw();
  t_ppt.DrawLatex(e1_ppt,y1_ppt+0.06/5,Form("#scale[%f]{1/2^{+}}",scale*0.75));

  Double_t y2_ppt=0.06;
  Double_t e2_ppt=2.285;
  TArrow a2_ppt(e2_ppt,y2_ppt,e2_ppt,y2_ppt+0.05/5,0.01,"<|");
  a2_ppt.SetLineColor(2);
  a2_ppt.SetFillColor(2);  
  a2_ppt.Draw();
  t_ppt.DrawLatex(e2_ppt,y2_ppt+0.06/5,Form("#scale[%f]{5/2^{+},7/2^{+}}",scale*0.75));

  Double_t y3_ppt=0.06;
  Double_t e3_ppt=2.750;
  TArrow a3_ppt(e3_ppt,y3_ppt,e3_ppt,y3_ppt+0.05/5,0.01,"<|");
  a3_ppt.SetLineColor(2);
  a3_ppt.SetFillColor(2);  
  a3_ppt.Draw();
  t_ppt.DrawLatex(e3_ppt,y3_ppt+0.06/5,Form("#scale[%f]{5/2^{+}}",scale*0.75));

  Double_t y4_ppt=0.04;
  Double_t e4_ppt=3.239;
  TArrow a4_ppt(e4_ppt,y4_ppt,e4_ppt,y4_ppt+0.05/5,0.01,"<|");
  a4_ppt.SetLineColor(2);
  a4_ppt.SetFillColor(2);  
  a4_ppt.Draw();
  t_ppt.DrawLatex(e4_ppt,y4_ppt+0.06/5,Form("#scale[%f]{5/2^{+}}",scale*0.75));

  TLatex t_pph;
  t_pph.SetTextColor(602);
  t_pph.SetTextAlign(12);
  t_pph.SetTextAngle(90);

  Double_t y0_pph=0.00;
  Double_t e0_pph=0.0;
  TArrow a0_pph(e0_pph,y0_pph-0.02,e0_pph,y0_pph-0.01,0.01,"|>");
  a0_pph.SetLineColor(602);
  a0_pph.SetFillColor(602);  
  a0_pph.Draw();
  t_pph.DrawLatex(e0_pph,-0.065,Form("#scale[%f]{3/2^{+} (g.s.)}",scale*0.75));

  Double_t y1_pph=0.00;
  Double_t e1_pph=1.409;
  TArrow a1_pph(e1_pph,-0.02,e1_pph,y1_pph-0.01,0.01,"|>");
  a1_pph.SetLineColor(602);
  a1_pph.SetFillColor(602);  
  a1_pph.Draw();
  t_pph.DrawLatex(e1_pph,-0.065,Form("#scale[%f]{1/2^{+}}",scale*0.75));

  Double_t y2_pph=0.00;
  Double_t e2_pph=2.217;
  TArrow a2_pph(e2_pph,-0.02,e2_pph,y2_pph-0.01,0.01,"|>");
  a2_pph.SetLineColor(602);
  a2_pph.SetFillColor(602);  
  a2_pph.Draw();
  t_pph.DrawLatex(e2_pph,-0.065,Form("#scale[%f]{7/2^{+}}",scale*0.75));


  Double_t y3_pph=0.00;
  Double_t e3_pph=2.796;
  TArrow a3_pph(e3_pph,-0.02,e3_pph,y3_pph-0.01,0.01,"|>");
  a3_pph.SetLineColor(602);
  a3_pph.SetFillColor(602);  
  a3_pph.Draw();
  t_pph.DrawLatex(e3_pph,-0.065,Form("#scale[%f]{5/2^{+}}",scale*0.75));

  Double_t y4_pph=0.00;
  Double_t e4_pph=3.170;
  TArrow a4_pph(e4_pph,-0.02,e4_pph,y4_pph-0.01,0.01,"|>");
  a4_pph.SetLineColor(602);
  a4_pph.SetFillColor(602);  
  a4_pph.Draw();
  t_pph.DrawLatex(e4_pph,-0.065,Form("#scale[%f]{5/2^{+}}",scale*0.75));

}
