{

  TFile *_file0 = TFile::Open("root/pph_48Ca.root");
  tree->Draw("phi:theta>>h(1000,49.5,52.0,1000,-4,4)","","colz");
  Double_t x[9] = {+49.7,+49.7,+50.2,+51.3,+51.7,+51.7,+51.3,+50.2,+49.7};
  Double_t y[9] = {-1.50,+1.50,+3.50,+3.50,+1.50,-1.50,-3.50,-3.50,-1.50};
  TPolyLine *pline = new TPolyLine(9,x,y);
  pline->SetLineColor(1);
  pline->SetLineWidth(2);
  //pline->Draw("f");                                                                                                                                             
  pline->Draw("same");

}
