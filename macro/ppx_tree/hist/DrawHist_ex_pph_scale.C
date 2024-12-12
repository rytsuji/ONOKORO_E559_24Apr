{
  int bin=2;
  double scale=1.0;
  
  double xmin=-5;
  double xmax=20;
  
  double ymin=-0.02; 
  double ymax=0.125;
  

  TCanvas *c1=new TCanvas("c1","",800,300);
  c1->Divide(2,1);
  c1->cd(1);
  TFile *file0 = TFile::Open("output/calib_pid/hist_ex/pph_carbon_carbon.nogate_raw.root");     
  sx->Rebin(bin);
  sx0->Rebin(bin);
  sx0->Sumw2(0);
  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);  
  sx->GetXaxis()->SetRange(sx->FindBin(xmin),sx->FindBin(xmax));
  sx->SetStats(0);
  sx->SetLineColor(602);
  sx->SetMarkerColor(602);
  sx0->SetLineColor(602);
  sx->Draw();
  sx0->Draw("same");
  sx->Fit("gausn","","",-5,1);
  

  //(p,pt) with angular gate
  TFile *file1 = TFile::Open("output/calib_pid/hist_ex/pph_carbon_carbon.root");
  c1->cd(2);
  sx->Rebin(bin);
  sx0->Rebin(bin);
  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);  
  sx->GetXaxis()->SetRange(sx->FindBin(xmin),sx->FindBin(xmax));
  sx->SetStats(0);
  sx->SetLineColor(602);
  sx->SetMarkerColor(602);
  sx0->SetLineColor(602);
  sx->Draw("");
  sx0->Draw("same");
  sx->Fit("gausn","","",-5,1);
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{12}C(#it{p,pt}/^{3}He)}",1.0*scale));

}
