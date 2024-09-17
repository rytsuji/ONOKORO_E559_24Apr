{

  TFile *_file0 = TFile::Open("root/pph_48Ca_las.root");
  tree->Draw("phi:theta>>h(1000,45,53,1000,175,185)","","colz");
  Double_t x[5] = {+45.9,+45.9,+52.7,+52.7,+45.9};
  Double_t y[5] = {176.5,183.5,183.5,176.5,176.5};
  TPolyLine *pline = new TPolyLine(5,x,y);
  pline->SetLineColor(1);
  pline->SetLineWidth(2);
  //pline->Draw("f");                                                                                                                                             
  pline->Draw("same");

}
