{
  int bin=5;
  double scale=1.0;

  double scale_ppt=1.46;
  double xmin=-5;
  double xmax=20;
  
  double ymin=-0.05; 
  double ymax=0.45;
  
  TFile *file0 = TFile::Open("output/calib_pid/hist_ex/ppt_mylar_oxygen.smeared.root");   
  TCanvas *c1=new TCanvas("c1","",800,600);
  
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear->Scale(scale_ppt);
  sx_smear0->Scale(scale_ppt);
  sx_smear0->Sumw2(0);
  sx_smear->SetMinimum(ymin);
  sx_smear->SetMaximum(ymax);  
  sx_smear->GetXaxis()->SetRange(sx_smear->FindBin(xmin),sx_smear->FindBin(xmax));
  sx_smear->SetStats(0);
  sx_smear->SetLineColor(2);
  sx_smear->SetMarkerColor(2);
  sx_smear0->SetLineColor(2);
  sx_smear->Draw();
  sx_smear0->Draw("same");

  

  //(p,ph)
  TFile *file1 = TFile::Open("output/calib_pid/hist_ex/pph_mylar_oxygen.root");
  sx->Rebin(bin);
  sx0->Rebin(bin);
  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);  
  sx->GetXaxis()->SetRange(sx->FindBin(xmin),sx->FindBin(xmax));
  sx->SetStats(0);
  sx->SetLineColor(602);
  sx->SetMarkerColor(602);
  sx0->SetLineColor(602);
  sx->Draw("same");
  sx0->Draw("same");

  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.5,.8,Form("#scale[%f]{Mylar(C_{10}H_{8}O_{4})(#it{p,pt}/^{3}He)}",1.0*scale));

}
