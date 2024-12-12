{
  int bin=10;
  double scale=1.0;
  
  double scale_ppt=1.46;
  //double scale_ppt=1.0;
  double xmin=-20;
  double xmax=25;
  
  double ymin=-0.05; 
  double ymax=0.5;

  double ymin_oxygen=-0.05; 
  double ymax_oxygen=0.35; 
  //double ymax=0.8;
  
  TFile *file0 = TFile::Open("output/calib_pid/hist_ex/ppt_oxygen.smeared.root");   
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
  TFile *file1 = TFile::Open("output/calib_pid/hist_ex/pph_oxygen.root");
  h_oxygen->Rebin(bin);
  h_oxygen0->Rebin(bin);
  h_oxygen->SetMinimum(ymin);
  h_oxygen->SetMaximum(ymax);  
  h_oxygen->GetXaxis()->SetRange(h_oxygen->FindBin(xmin),h_oxygen->FindBin(xmax));
  h_oxygen->SetStats(0);
  h_oxygen->SetLineColor(602);
  h_oxygen->SetMarkerColor(602);
  h_oxygen0->SetLineColor(602);
  h_oxygen->Draw("same");
  h_oxygen0->Draw("same");

  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{16}O(#it{p,pt})}",1.0*scale));

}
