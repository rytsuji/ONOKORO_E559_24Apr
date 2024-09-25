{

  //"abs(pgr.GetTheta()-51.2)<1.0 && abs(pgr.GetPhi())<3.5 && abs(pgr.GetPhi())<(4.0*pgr.GetTheta()-199.3) && abs(pgr.GetPhi())<(-5.0*pgr.GetTheta()+262.5)"

  TFile *_file0 = TFile::Open("root/pph_48Ca.root");
  TCanvas *c1 =new TCanvas("c1","",800,600);
  TH2F *h = new TH2F("h","",1000,49.2,52.0,1000,-5,5);
  h->GetXaxis()->SetTitle("#theta_{GR} (deg)");
  h->GetYaxis()->SetTitle("#phi_{GR} (deg)");
  h->SetStats(0);

  tree->Draw("phi:theta>>h","","colz");
  Double_t x[9] = {+49.7,+49.7,+50.2,+51.3,+51.7,+51.7,+51.3,+50.2,+49.7};
  Double_t y[9] = {-1.50,+1.50,+3.50,+3.50,+1.50,-1.50,-3.50,-3.50,-1.50};
  TPolyLine *pline = new TPolyLine(9,x,y);
  pline->SetLineColor(1);
  pline->SetLineWidth(2);
  //pline->Draw("f");
  pline->Draw("same");



  TLine *lv1 = new TLine(49.7,-5,49.7,5);
  TLine *lv2 = new TLine(50.2,-5,50.2,5);
  TLine *lv3 = new TLine(51.3,-5,51.3,5);
  TLine *lv4 = new TLine(51.7,-5,51.7,5);

  TLine *lh1 = new TLine(49.2,-3.5,52.,-3.5);
  TLine *lh2 = new TLine(49.2,-1.5,52.,-1.5);
  TLine *lh3 = new TLine(49.2,+1.5,52.,+1.5);
  TLine *lh4 = new TLine(49.2,+3.5,52.,+3.5);

  lv1->SetLineStyle(2);
  lv2->SetLineStyle(2);
  lv3->SetLineStyle(2);
  lv4->SetLineStyle(2);

  lh1->SetLineStyle(2);
  lh2->SetLineStyle(2);
  lh3->SetLineStyle(2);
  lh4->SetLineStyle(2);        
  
  lv1->Draw("same");
  lv2->Draw("same");
  lv3->Draw("same");
  lv4->Draw("same");

  lh1->Draw("same");
  lh2->Draw("same");
  lh3->Draw("same");
  lh4->Draw("same");  
    
  TLatex t0;
  t0.DrawLatex(49.5,-4.5,"#scale[0.7]{#theta=49.7^{#circ}}");
  t0.DrawLatex(50.05,-4.5,"#scale[0.7]{#theta=50.2^{#circ}}");
  t0.DrawLatex(51.05,-4.5,"#scale[0.7]{#theta=51.3^{#circ}}");
  t0.DrawLatex(51.55,-4.5,"#scale[0.7]{#theta=51.7^{#circ}}");      

  t0.DrawLatex(49.3,-3.5+0.1,"#scale[0.7]{#phi=-3.5^{#circ}}");
  t0.DrawLatex(49.3,-1.5+0.1,"#scale[0.7]{#phi=-1.5^{#circ}}");
  t0.DrawLatex(49.3,1.5+0.1,"#scale[0.7]{#phi=1.5^{#circ}}");
  t0.DrawLatex(49.3,3.5+0.1,"#scale[0.7]{#phi=3.5^{#circ}}");    

  c1->SaveAs("../../figs/d_thesis/acc_pph_48Ca_lab.pdf");
  c1->SaveAs("../../figs/d_thesis/acc_pph_48Ca_lab.png");
}
