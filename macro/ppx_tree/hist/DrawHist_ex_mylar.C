{
  int bin=10;
  double scale=1.0;

  double scale_ppt=1.46;
  double xmin=-20;
  double xmax=25;
  
  double ymin=-0.02; 
  double ymax=0.8;

  double ymin_oxygen=-0.05; 
  double ymax_oxygen=0.35; 
  //double ymax=0.8;
  
  TFile *file0 = TFile::Open("output/calib_pid/hist_ex/ppt_oxygen.root");   
  TCanvas *c1=new TCanvas("c1","",1200*0.8,600*0.8);
  c1->Divide(3,2);
  c1->cd(1);
  h_mylar->Rebin(bin);
  h_mylar0->Rebin(bin);
  h_mylar->SetMinimum(ymin);
  h_mylar->SetMaximum(ymax);  
  h_mylar->GetXaxis()->SetRange(h_mylar->FindBin(xmin),h_mylar->FindBin(xmax));
  h_mylar->SetStats(0);
  h_mylar->Draw();
  h_mylar0->Draw("same");

  h_carbon->Rebin(bin);
  h_carbon0->Rebin(bin);  
  h_carbon->Draw("same");
  h_carbon0->Draw("same");  


  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{nat}C/Mylar(#it{p,pt})}",1.0*scale));

  c1->cd(4);
  h_oxygen->Rebin(bin);
  h_oxygen0->Rebin(bin);
  h_oxygen->SetMinimum(ymin_oxygen);
  h_oxygen->SetMaximum(ymax_oxygen);  
  h_oxygen->GetXaxis()->SetRange(h_oxygen->FindBin(xmin),h_oxygen->FindBin(xmax));
  h_oxygen->SetStats(0);
  h_oxygen->SetLineColor(602);
  h_oxygen->SetMarkerColor(602);
  h_oxygen0->SetLineColor(602);
  h_oxygen->Draw();
  h_oxygen0->Draw("same");
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{16}O(#it{p,pt})}",1.0*scale));
  title.DrawLatex(.55,.7,Form("#scale[%f]{#it{S_{t}}=25.032 (MeV)}",1.0*scale));  
  //(p,ph)
  TFile *file1 = TFile::Open("output/calib_pid/hist_ex/pph_oxygen.root");
  c1->cd(2);
  h_mylar->Rebin(bin);
  h_mylar0->Rebin(bin);
  h_mylar->SetMinimum(ymin);
  h_mylar->SetMaximum(ymax);  
  h_mylar->GetXaxis()->SetRange(h_mylar->FindBin(xmin),h_mylar->FindBin(xmax));
  h_mylar->SetStats(0);
  h_mylar->Draw();
  h_mylar0->Draw("same");

  h_carbon->Rebin(bin);
  h_carbon0->Rebin(bin);  
  h_carbon->Draw("same");
  h_carbon0->Draw("same");  
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{nat}C/Mylar(#it{p,p}^{3}He)}",1.0*scale));

  c1->cd(5);
  h_oxygen->Rebin(bin);
  h_oxygen0->Rebin(bin);
  h_oxygen->SetMinimum(ymin_oxygen);
  h_oxygen->SetMaximum(ymax_oxygen);  
  h_oxygen->GetXaxis()->SetRange(h_oxygen->FindBin(xmin),h_oxygen->FindBin(xmax));
  h_oxygen->SetStats(0);
  h_oxygen->SetLineColor(602);
  h_oxygen->SetMarkerColor(602);
  h_oxygen0->SetLineColor(602);
  h_oxygen->Draw();
  h_oxygen0->Draw("same");
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{16}O(#it{p,p}^{3}He})",1.0*scale));
  title.DrawLatex(.55,.7,Form("#scale[%f]{#it{S_{^{3}He}}=22.793 (MeV)}",1.0*scale));
    
  //(p,ph) 48Ca setup
  TFile *file2 = TFile::Open("output/calib_pid/hist_ex/pph_48Ca_oxygen.root");
  c1->cd(3);
  h_mylar->Rebin(bin);
  h_mylar0->Rebin(bin);
  h_mylar->SetMinimum(ymin);
  h_mylar->SetMaximum(ymax);  
  h_mylar->GetXaxis()->SetRange(h_mylar->FindBin(xmin),h_mylar->FindBin(xmax));
  h_mylar->SetStats(0);
  h_mylar->Draw();
  h_mylar0->Draw("same");

  h_carbon->Rebin(bin);
  h_carbon0->Rebin(bin);  
  h_carbon->Draw("same");
  h_carbon0->Draw("same");  
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{nat}C/Mylar(#it{p,p}^{3}He)}",1.0*scale));
  title.DrawLatex(.55,.7,Form("#scale[%f]{^{48}Ca(#it{p,p}^{3}He) setup}",1.0*scale));  

  c1->cd(6);
  h_oxygen->Rebin(bin);
  h_oxygen0->Rebin(bin);
  h_oxygen->SetMinimum(ymin_oxygen);
  h_oxygen->SetMaximum(ymax_oxygen);  
  h_oxygen->GetXaxis()->SetRange(h_oxygen->FindBin(xmin),h_oxygen->FindBin(xmax));
  h_oxygen->SetStats(0);
  h_oxygen->SetLineColor(602);
  h_oxygen->SetMarkerColor(602);
  h_oxygen0->SetLineColor(602);
  h_oxygen->Draw();
  h_oxygen0->Draw("same");
  title.DrawLatex(.55,.8,Form("#scale[%f]{^{16}O(#it{p,p}^{3}He)}",1.0*scale));
  title.DrawLatex(.55,.7,Form("#scale[%f]{^{48}Ca(#it{p,p}^{3}He) setup}",1.0*scale));  
}
