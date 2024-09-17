{

  TFile *_file0 = TFile::Open("root/ppt_las.root");
  tree->Draw("phi:theta>>h(1000,47,55,1000,175,185)","","colz");
  Double_t x[5] = {+47.5,+47.5,+54.3,+54.3,+47.5};
  Double_t y[5] = {176.5,183.5,183.5,176.5,176.5};
  TPolyLine *pline = new TPolyLine(5,x,y);
  pline->SetLineColor(1);
  pline->SetLineWidth(2);
  //pline->Draw("f");                                                                                                                                             
  pline->Draw("same");

}
