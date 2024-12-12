{
  int bin=10;// 0.5 MeV
  //int bin=20;
  double scale=1.0;
  double scale_ppt=1.0;
  //double scale_ppt=1.7891074;
  //double scale_ppt=1.46;
  double xmin=-20;
  double xmax=20;
  double ymin=-0.05; 
  double ymax=0.2; // 0.5 MeV
  //double ymax=0.3;
  
  TFile *file0 = TFile::Open("output/ppx_ex/pph_40Ca.weight.root");   
  TCanvas *c1=new TCanvas("c1","",800,600);
  c1->Divide(2,2);
  c1->cd(1);
  sx_weight->Rebin(bin);
  sx_weight0->Rebin(bin);
  sx_weight->SetMinimum(ymin);
  sx_weight->SetMaximum(ymax);  
  sx_weight->GetXaxis()->SetRange(sx_weight->FindBin(xmin),sx_weight->FindBin(xmax));
  sx_weight->SetStats(0);
  sx_weight->Draw();
  sx_weight0->Draw("same");

  TFile *file1 = TFile::Open("output/ppx_ex/ppt_40Ca.weight.root"); 
  sx_weight->Scale(scale_ppt);
  sx_weight0->Scale(scale_ppt);
  sx_weight->Rebin(bin);
  sx_weight0->Rebin(bin);
  sx_weight->Draw("same");
  sx_weight0->Draw("same");

  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{40}Ca}",1.0*scale));
  
  //42Ca
  TFile *file2 = TFile::Open("output/ppx_ex/pph_42Ca.weight.root");   
  c1->cd(2);
  sx_weight->Rebin(bin);
  sx_weight0->Rebin(bin);
  sx_weight->SetMinimum(ymin);
  sx_weight->SetMaximum(ymax);  
  sx_weight->GetXaxis()->SetRange(sx_weight->FindBin(xmin),sx_weight->FindBin(xmax));
  sx_weight->SetStats(0);
  sx_weight->Draw();
  sx_weight0->Draw("same");

  TFile *file3 = TFile::Open("output/ppx_ex/ppt_42Ca.weight.root"); 
  sx_weight->Scale(scale_ppt);
  sx_weight0->Scale(scale_ppt);
  sx_weight->Rebin(bin);
  sx_weight0->Rebin(bin);
  sx_weight->Draw("same");
  sx_weight0->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{42}Ca}",1.0*scale));

  //44Ca
  TFile *file4 = TFile::Open("output/ppx_ex/ppt_44Ca.weight.root");   
  c1->cd(3);
  sx_weight->Scale(scale_ppt);
  sx_weight0->Scale(scale_ppt);
  sx_weight->Rebin(bin);
  sx_weight0->Rebin(bin);
  sx_weight->SetMinimum(ymin);
  sx_weight->SetMaximum(ymax);  
  sx_weight->GetXaxis()->SetRange(sx_weight->FindBin(xmin),sx_weight->FindBin(xmax));
  sx_weight->SetStats(0);
  sx_weight->Draw();
  sx_weight0->Draw("same");

  TFile *file5 = TFile::Open("output/ppx_ex/pph_44Ca.weight.root"); 
  sx_weight->Rebin(bin);
  sx_weight0->Rebin(bin);
  sx_weight->Draw("same");
  sx_weight0->Draw("same");
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{44}Ca}",1.0*scale));

  //48Ca
  TFile *file6 = TFile::Open("output/ppx_ex/ppt_48Ca.weight.root");   
  c1->cd(4);
  sx_weight->Scale(scale_ppt);
  sx_weight0->Scale(scale_ppt);
  sx_weight->Rebin(bin);
  sx_weight0->Rebin(bin);
  sx_weight->SetMinimum(ymin);
  sx_weight->SetMaximum(ymax);  
  sx_weight->GetXaxis()->SetRange(sx_weight->FindBin(xmin),sx_weight->FindBin(xmax));
  sx_weight->SetStats(0);
  sx_weight->Draw();
  sx_weight0->Draw("same");

  TFile *file7 = TFile::Open("output/ppx_ex/pph_48Ca.weight.root"); 
  sx_weight->Rebin(bin);
  sx_weight0->Rebin(bin);
  sx_weight->Draw("same");
  sx_weight0->Draw("same");

  title.DrawLatex(.65,.8,Form("#scale[%f]{^{48}Ca}",1.0*scale));
}
