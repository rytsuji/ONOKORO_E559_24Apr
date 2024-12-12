
//run1036 delta=101%
{
  ofstream ofile1("work/fp_gr/dat/delta101.dat");
  ofstream ofile2("work/fp_gr/fit/delta101_fit.dat");
  TFile *_file0 = TFile::Open("output/gr/run1036.root");
  TH2F *hxa=new TH2F("hxa","GR VDC x(mm) vs a(rad)",100,180,230,88,-0.030,0.058);
  tree->Draw("gdc.fA:gdc.fX>>h(1000,-1000,1000,1000,-0.08,0.08)");
  tree->Draw("gdc.fA:gdc.fX>>hxa");
  hxa->FitSlicesX();
  gApplication->ProcessLine("gcom delta101 run1036");
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht hxa_1");

  int xbin=hxa_1->GetXaxis()->GetNbins();
  for(int i=0; i< xbin; i++){
    double x=hxa_1->GetBinContent(i);
    double a=hxa_1->GetXaxis()->GetBinCenter(i);
    ofile1 << "-0.01 " << x << " " << a << std::endl;
  }
  ofile1.close();
  TF1 *f = new TF1("f","pol4",-1.0,1.0);
  hxa_1->Fit("f");
  for(int i=0;i<5;i++){
    ofile2 << f->GetParameter(i) << " " ;
  }
  ofile2 << std::endl;
  ofile2.close();
}
