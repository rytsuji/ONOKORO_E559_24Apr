{


  TFile *_file0 = TFile::Open("root/pph_48Ca_las.root");
  TCanvas *c1 =new TCanvas("c1","",800,600);
  TH2F *h=new TH2F("h","",1000,44,53,1000,173,187);
  h->GetXaxis()->SetTitle("#theta_{LAS} (deg)");                                                                                                                 
  h->GetYaxis()->SetTitle("#phi_{LAS} (deg)");   
  h->SetStats(0);
  tree->Draw("phi:theta>>h","","colz");
  Double_t x[5] = {+45.9,+45.9,+52.7,+52.7,+45.9};
  Double_t y[5] = {176.5,183.5,183.5,176.5,176.5};
  TPolyLine *pline = new TPolyLine(5,x,y);
  pline->SetLineColor(1);
  pline->SetLineWidth(2);
  //pline->Draw("f");
  
  pline->Draw("same");

  TLine *lv1 = new TLine(45.9,173,45.9,187);
  TLine *lv2 = new TLine(52.7,173,52.7,187);

  TLine *lh1 = new TLine(44,176.5,54,176.5);
  TLine *lh2 = new TLine(44,183.5,54,183.5);  

  lv1->SetLineStyle(2);
  lv2->SetLineStyle(2);

  lh1->SetLineStyle(2);
  lh2->SetLineStyle(2);

  lv1->Draw("same");
  lv2->Draw("same");
  
  lh1->Draw("same");
  lh2->Draw("same");

  TLatex t0;

  t0.DrawLatex(44.9,174,"#scale[0.7]{#theta=45.9^{#circ}}");
  t0.DrawLatex(51.6,174,"#scale[0.7]{#theta=52.7^{#circ}}");

  t0.DrawLatex(44.4,177,"#scale[0.7]{#phi=176.5^{#circ}}");
  t0.DrawLatex(44.4,184.2,"#scale[0.7]{#phi=183.5^{#circ}}");
        
  c1->SaveAs("../../figs/d_thesis/acc_pph_48Ca_las_lab.pdf");
  c1->SaveAs("../../figs/d_thesis/acc_pph_48Ca_las_lab.png");
}
