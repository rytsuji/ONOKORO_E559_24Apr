{
  int bin=20; //1MeV
  double scale=1.0;
 
  //double scale_ppt=1.0;
  //double scale_ppt=1.7891074;
  double scale_ppt=1.46;
  double xmin=-1;
  double xmax=20;
  double ymin=-0.05*2.0; 
  //double ymax=0.175; 
  double ymax=0.17*2.0;

  TLine *lz = new TLine(xmin,0,xmax,0);
  lz->SetLineStyle(2);
  lz->SetLineWidth(3);
  
  TFile *file0 = TFile::Open("output/calib_pid/hist_ex/pph_40Ca.root");   
  TCanvas *c1=new TCanvas("c1","",800,600);
  c1->Divide(2,2);
  c1->cd(1);
  h_40Ca->Rebin(bin);
  h_40Ca0->Rebin(bin);
  h_40Ca->SetMinimum(ymin);
  h_40Ca->SetMaximum(ymax);  
  h_40Ca->GetXaxis()->SetRange(h_40Ca->FindBin(xmin),h_40Ca->FindBin(xmax));
  h_40Ca->SetStats(0);
  h_40Ca->Draw("E1");
  h_40Ca0->Draw("same");

  TFile *file1 = TFile::Open("output/calib_pid/hist_ex/ppt_40Ca.root"); 
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

  lz->Draw("same");
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{40}Ca}",1.0*scale));
  
  //42Ca
  TFile *file2 = TFile::Open("output/calib_pid/hist_ex/pph_42Ca.root");   
  c1->cd(2);
  h_42Ca->Rebin(bin);
  h_42Ca0->Rebin(bin);
  h_42Ca->SetMinimum(ymin);
  h_42Ca->SetMaximum(ymax);  
  h_42Ca->GetXaxis()->SetRange(h_42Ca->FindBin(xmin),h_42Ca->FindBin(xmax));
  h_42Ca->SetStats(0);
  h_42Ca->Draw("E1");
  h_42Ca0->Draw("same");

  TFile *file3 = TFile::Open("output/calib_pid/hist_ex/ppt_42Ca.root"); 
  h_42Ca->Scale(scale_ppt);
  h_42Ca0->Scale(scale_ppt);
  h_42Ca->Rebin(bin);
  h_42Ca0->Rebin(bin);
  h_42Ca0->Sumw2(0);
  h_42Ca->SetLineColor(2);
  h_42Ca->SetMarkerColor(2);  
  h_42Ca0->SetLineColor(2);
  h_42Ca->Draw("same E1");
  h_42Ca0->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{42}Ca}",1.0*scale));

  lz->Draw("same");
  //44Ca
  TFile *file4 = TFile::Open("output/calib_pid/hist_ex/ppt_44Ca.root");   
  c1->cd(3);
  h_44Ca->Scale(scale_ppt);
  h_44Ca0->Scale(scale_ppt);
  h_44Ca->Rebin(bin);
  h_44Ca0->Rebin(bin);
  h_44Ca0->Sumw2(0);
  h_44Ca->SetMinimum(ymin);
  h_44Ca->SetMaximum(ymax);  
  h_44Ca->GetXaxis()->SetRange(h_44Ca->FindBin(xmin),h_44Ca->FindBin(xmax));
  h_44Ca->SetStats(0);
  h_44Ca->SetLineColor(2);
  h_44Ca->SetMarkerColor(2);  
  h_44Ca0->SetLineColor(2);
  h_44Ca->Draw("E1");
  h_44Ca0->Draw("same");

  TFile *file5 = TFile::Open("output/calib_pid/hist_ex/pph_44Ca.root"); 
  h_44Ca->Rebin(bin);
  h_44Ca0->Rebin(bin);
  h_44Ca->Draw("same E1");
  h_44Ca0->Draw("same");
  lz->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{44}Ca}",1.0*scale));

  
  //48Ca
  TFile *file6 = TFile::Open("output/calib_pid/hist_ex/ppt_48Ca.root");   
  c1->cd(4);
  h_48Ca->Scale(scale_ppt);
  h_48Ca0->Scale(scale_ppt);
  h_48Ca->Rebin(bin);
  h_48Ca0->Rebin(bin);
  h_48Ca0->Sumw2(0);
  h_48Ca->SetMinimum(ymin);
  h_48Ca->SetMaximum(ymax);  
  h_48Ca->GetXaxis()->SetRange(h_48Ca->FindBin(xmin),h_48Ca->FindBin(xmax));
  h_48Ca->SetStats(0);
  h_48Ca->SetLineColor(2);
  h_48Ca->SetMarkerColor(2);  
  h_48Ca0->SetLineColor(2);
  h_48Ca->Draw("E1");
  h_48Ca0->Draw("same");

  TFile *file7 = TFile::Open("output/calib_pid/hist_ex/pph_48Ca.root"); 
  h_48Ca->Rebin(bin);
  h_48Ca0->Rebin(bin);
  h_48Ca->Draw("same E1");
  h_48Ca0->Draw("same");
  lz->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{48}Ca}",1.0*scale));
}
