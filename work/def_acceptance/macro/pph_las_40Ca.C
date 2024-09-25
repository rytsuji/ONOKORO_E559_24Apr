{

  TFile *_file0 = TFile::Open("root/ppt_las.root");
  TCanvas *c1 =new TCanvas("c1","",800,600);
  TH2F *h=new TH2F("h","",1000,45.5,55,1000,173,187);
  h->GetXaxis()->SetTitle("#theta_{LAS} (deg)");
  h->GetYaxis()->SetTitle("#phi_{LAS} (deg)");
  h->SetStats(0);
  tree->Draw("phi:theta>>h","","colz");
  Double_t x[5] = {+49,+49,+54,+54,+49};
  Double_t y[5] = {176.5,183.5,183.5,176.5,176.5};
  TPolyLine *pline = new TPolyLine(5,x,y);
  pline->SetLineColor(1);
  pline->SetLineWidth(2);
  //pline->Draw("f");                                                                                                                                            
  pline->Draw("same");

  TLine *lv1 = new TLine(49,173,49,187);
  TLine *lv2 = new TLine(54,173,54,187);

  TLine *lh1 = new TLine(45.5,176.5,55,176.5);
  TLine *lh2 = new TLine(45.6,183.5,55,183.5);

  lv1->SetLineStyle(2);
  lv2->SetLineStyle(2);

  lh1->SetLineStyle(2);
  lh2->SetLineStyle(2);

  lv1->Draw("same");
  lv2->Draw("same");
  
  lh1->Draw("same");
  lh2->Draw("same");

  TLatex t0;

  t0.DrawLatex(48,174,"#scale[0.7]{#theta=49^{#circ}}");
  t0.DrawLatex(53.2,174,"#scale[0.7]{#theta=54^{#circ}}");

  t0.DrawLatex(45.8,177,"#scale[0.7]{#phi=176.5^{#circ}}");
  t0.DrawLatex(45.8,184.2,"#scale[0.7]{#phi=183.5^{#circ}}");

  c1->SaveAs("../../figs/d_thesis/acc_pph_las_lab_40Ca.pdf");
  c1->SaveAs("../../figs/d_thesis/acc_pph_las_lab_40Ca.png");
  
}
