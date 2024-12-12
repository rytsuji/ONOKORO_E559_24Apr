{

  TCanvas *c1 =new TCanvas("c1","c1",800,600);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  c1->SetLogz();

  TH2F *h=new TH2F("h","",500,0,142.07,1000,0,4000);  
  h->SetStats(0);

  tree->Draw("pid_gr.fCharge:fmod(pid_gr.fTiming-pgr.GetTOFDiff()-rf2.fTiming+1420.675,142.0675)>>h","","colz");

  b1=new TBox(32,0.1,39,3500);
  b1->SetFillStyle(0);
  b1->Draw();

  double dRF=142.0675/2;
  b2=new TBox(32+dRF,0.1,39+dRF,3500);
  b2->SetFillStyle(0);
  b2->Draw();

  TLatex xtitle;
  xtitle.SetTextAlign(22);
  xtitle.SetNDC(1);
  xtitle.SetTextAngle(0);
  xtitle.DrawLatex(0.5,0.05,"#scale[0.8]{RF_{GR}}");

  TLatex ytitle;
  ytitle.SetTextAlign(22);
  ytitle.SetNDC(1);
  ytitle.SetTextAngle(90);
  ytitle.DrawLatex(0.05,0.5,"#scale[0.8]{plastic_{GR} #it{#Delta E}}");
}
