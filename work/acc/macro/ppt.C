{

  //"abs(pgr.GetTheta()-51.2)<1.0 && abs(pgr.GetPhi())<3.5 && abs(pgr.GetPhi())<(4.0*pgr.GetTheta()-199.3) && abs(pgr.GetPhi())<(-5.0*pgr.GetTheta()+262.5)"
  
  TFile *_file0 = TFile::Open("root/ppt.root");
  tree->Draw("phi:theta>>h(1000,50,52.5,1000,-4,4)","","colz");
  Double_t x[9] = {+50.2,+50.2,+50.7,+51.8,+52.2,+52.2,+51.8,+50.7,+50.2};
  Double_t y[9] = {-1.50,+1.50,+3.50,+3.50,+1.50,-1.50,-3.50,-3.50,-1.50};
  TPolyLine *pline = new TPolyLine(9,x,y);
  pline->SetLineColor(1);
  pline->SetLineWidth(2);
  //pline->Draw("f");
  
  pline->Draw("same");

}
