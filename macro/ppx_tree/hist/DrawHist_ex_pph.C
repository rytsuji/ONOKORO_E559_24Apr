{
  int bin=10;
  double scale=1.0;
 
  //double scale_ppt=1.0;
  //double scale_ppt=1.7891074;
  double scale_ppt=1.46;
  double xmin=-20;
  double xmax=20;
  double ymin=-0.02; 
  double ymax=0.15; 
  //double ymax=0.8;
  
  TFile *file0 = TFile::Open("output/calib_pid/hist_ex/pph_40Ca.root");   
  TCanvas *c1=new TCanvas("c1","",800,600);
  c1->Divide(2,2);
  c1->cd(1);
  h_40Ca_raw->Rebin(bin);
  h_40Ca0_raw->Rebin(bin);
  h_40Ca_raw->SetMinimum(ymin);
  h_40Ca_raw->SetMaximum(ymax);  
  h_40Ca_raw->GetXaxis()->SetRange(h_40Ca_raw->FindBin(xmin),h_40Ca_raw->FindBin(xmax));
  h_40Ca_raw->SetStats(0);
  h_40Ca_raw->Draw();
  h_40Ca0_raw->Draw("same");

  h_oxygen->Rebin(bin);
  h_oxygen0->Rebin(bin);  
  h_oxygen->Draw("same");
  h_oxygen0->Draw("same");

  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{40}Ca(#it{p,p}^{3}He)}",1.0*scale));
  
  //42Ca
  TFile *file1 = TFile::Open("output/calib_pid/hist_ex/pph_42Ca.root");   
  c1->cd(2);
  h_42Ca_raw->Rebin(bin);
  h_42Ca0_raw->Rebin(bin);
  h_42Ca_raw->SetMinimum(ymin);
  h_42Ca_raw->SetMaximum(ymax);  
  h_42Ca_raw->GetXaxis()->SetRange(h_42Ca_raw->FindBin(xmin),h_42Ca_raw->FindBin(xmax));
  h_42Ca_raw->SetStats(0);
  h_42Ca_raw->Draw();
  h_42Ca0_raw->Draw("same");

  h_oxygen->Rebin(bin);
  h_oxygen0->Rebin(bin);  
  h_oxygen->Draw("same");
  h_oxygen0->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{42}Ca(#it{p,p}^{3}He)}",1.0*scale));



  //44Ca
  TFile *file2 = TFile::Open("output/calib_pid/hist_ex/pph_44Ca.root");   
  c1->cd(3);
  h_44Ca_raw->Rebin(bin);
  h_44Ca0_raw->Rebin(bin);
  h_44Ca_raw->SetMinimum(ymin);
  h_44Ca_raw->SetMaximum(ymax);  
  h_44Ca_raw->GetXaxis()->SetRange(h_44Ca_raw->FindBin(xmin),h_44Ca_raw->FindBin(xmax));
  h_44Ca_raw->SetStats(0);
  h_44Ca_raw->Draw();
  h_44Ca0_raw->Draw("same");

  h_oxygen->Rebin(bin);
  h_oxygen0->Rebin(bin);  
  h_oxygen->Draw("same");
  h_oxygen0->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{44}Ca(#it{p,p}^{3}He)}",1.0*scale));


  //48Ca
  TFile *file3 = TFile::Open("output/calib_pid/hist_ex/pph_48Ca.root");   
  c1->cd(4);
  h_48Ca_raw->Rebin(bin);
  h_48Ca0_raw->Rebin(bin);
  h_48Ca_raw->SetMinimum(ymin);
  h_48Ca_raw->SetMaximum(ymax);  
  h_48Ca_raw->GetXaxis()->SetRange(h_48Ca_raw->FindBin(xmin),h_48Ca_raw->FindBin(xmax));
  h_48Ca_raw->SetStats(0);
  h_48Ca_raw->Draw();
  h_48Ca0_raw->Draw("same");

  h_oxygen->Rebin(bin);
  h_oxygen0->Rebin(bin);  
  h_oxygen->Draw("same");
  h_oxygen0->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{48}Ca(#it{p,p}^{3}He)}",1.0*scale));



}
