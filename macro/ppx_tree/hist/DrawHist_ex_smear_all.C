{
  int bin=10;
  double scale=1.0;
 
  //double scale_ppt=1.0;
  //double scale_ppt=1.7891074;
  double scale_ppt=1.46;
  double xmin=-2;
  double xmax=18;
  double ymin=-0.05; 
  double ymax=0.17; 
  //double ymax=0.8;

  TLine *lz = new TLine(xmin,0,xmax,0);
  lz->SetLineStyle(2);
  lz->SetLineWidth(3);
  
  TFile *file0 = TFile::Open("output/calib_pid/hist_ex/pph_40Ca.smeared.root");
  TCanvas *c1=new TCanvas("c1","",800,600);
  c1->Divide(2,2);
  c1->cd(1);
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear->SetMinimum(ymin);
  sx_smear->SetMaximum(ymax);  
  sx_smear->GetXaxis()->SetRange(sx_smear->FindBin(xmin),sx_smear->FindBin(xmax));
  sx_smear->SetStats(0);
  sx_smear->Draw("E1");
  sx_smear0->Draw("same");

  TFile *file1 = TFile::Open("output/calib_pid/hist_ex/ppt_40Ca.smeared.root"); 
  sx_smear->Scale(scale_ppt);
  sx_smear0->Scale(scale_ppt);
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear0->Sumw2(0);
  sx_smear->SetLineColor(2);
  sx_smear->SetMarkerColor(2);  
  sx_smear0->SetLineColor(2);
  sx_smear->Draw("same E1");
  sx_smear0->Draw("same");

  lz->Draw("same");
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{40}Ca}",1.0*scale));
  
  //42Ca
  TFile *file2 = TFile::Open("output/calib_pid/hist_ex/pph_42Ca.smeared.root");
  c1->cd(2);
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear->SetMinimum(ymin);
  sx_smear->SetMaximum(ymax);  
  sx_smear->GetXaxis()->SetRange(sx_smear->FindBin(xmin),sx_smear->FindBin(xmax));
  sx_smear->SetStats(0);
  sx_smear->Draw("E1");
  sx_smear0->Draw("same");

  TFile *file3 = TFile::Open("output/calib_pid/hist_ex/ppt_42Ca.smeared.root"); 
  sx_smear->Scale(scale_ppt);
  sx_smear0->Scale(scale_ppt);
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear0->Sumw2(0);
  sx_smear->SetLineColor(2);
  sx_smear->SetMarkerColor(2);  
  sx_smear0->SetLineColor(2);
  sx_smear->Draw("same E1");
  sx_smear0->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{42}Ca}",1.0*scale));

  lz->Draw("same");
  //44Ca
  TFile *file4 = TFile::Open("output/calib_pid/hist_ex/ppt_44Ca.smeared.root");   
  c1->cd(3);
  sx_smear->Scale(scale_ppt);
  sx_smear0->Scale(scale_ppt);
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear0->Sumw2(0);
  sx_smear->SetMinimum(ymin);
  sx_smear->SetMaximum(ymax);  
  sx_smear->GetXaxis()->SetRange(sx_smear->FindBin(xmin),sx_smear->FindBin(xmax));
  sx_smear->SetStats(0);
  sx_smear->SetLineColor(2);
  sx_smear->SetMarkerColor(2);  
  sx_smear0->SetLineColor(2);
  sx_smear->Draw("E1");
  sx_smear0->Draw("same");

  TFile *file5 = TFile::Open("output/calib_pid/hist_ex/pph_44Ca.smeared.root");
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear->Draw("same E1");
  sx_smear0->Draw("same");
  lz->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{44}Ca}",1.0*scale));

  
  //48Ca
  TFile *file6 = TFile::Open("output/calib_pid/hist_ex/ppt_48Ca.smeared.root");   
  c1->cd(4);
  sx_smear->Scale(scale_ppt);
  sx_smear0->Scale(scale_ppt);
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear0->Sumw2(0);
  sx_smear->SetMinimum(ymin);
  sx_smear->SetMaximum(ymax);  
  sx_smear->GetXaxis()->SetRange(sx_smear->FindBin(xmin),sx_smear->FindBin(xmax));
  sx_smear->SetStats(0);
  sx_smear->SetLineColor(2);
  sx_smear->SetMarkerColor(2);  
  sx_smear0->SetLineColor(2);
  sx_smear->Draw("E1");
  sx_smear0->Draw("same");

  TFile *file7 = TFile::Open("output/calib_pid/hist_ex/pph_48Ca.smeared.root");
  sx_smear->Rebin(bin);
  sx_smear0->Rebin(bin);
  sx_smear->Draw("same E1");
  sx_smear0->Draw("same");
  lz->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{48}Ca}",1.0*scale));
}
