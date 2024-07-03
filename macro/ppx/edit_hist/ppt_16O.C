{

  pad0->cd();
  TFile *_file0 = TFile::Open("macro/ppx/output_sx/ppt_16O_tave.root");
  sx_oxygen->Scale(0.10182669*(10.47/48.0080)/(11.8/39.962));
  sx_oxygen->Sumw2(0);
  sx_oxygen->SetLineColor(1);
  sx_oxygen->SetLineWidth(2);
  //sx_oxygen->SetFillColor(14);
  sx_oxygen->Draw("same");


  pad1->cd();
  TFile *_file1 = TFile::Open("macro/ppx/output_sx/ppt_16O_tave.root");
  sx_oxygen->Scale(0.41272537);
  sx_oxygen->Sumw2(0);
  sx_oxygen->SetLineColor(1);
  sx_oxygen->SetLineWidth(2);  
  //sx_oxygen->SetFillColor(14);
  sx_oxygen->Draw("same");






}
