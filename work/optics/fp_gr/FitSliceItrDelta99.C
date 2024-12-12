//run1040 delta=99%
{
  //ofstream ofile1("work/fp_gr/dat/delta99.dat");
  //ofstream ofile2("work/fp_gr/fit/delta99_fit.dat");
  TFile *_file0 = TFile::Open("output/gr/run1040.root");
  TH2F *hxa=new TH2F("hxa","GR VDC x(mm) vs a(rad)",100,-250,-200,92,-0.052,0.04);
  tree->Draw("gdc.fA:gfp.fX>>hxa");
  hxa->FitSlicesX();
  gApplication->ProcessLine("gcom delta99 run1040");
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht hxa_1");
  /*
  int xbin=hxa_1->GetXaxis()->GetNbins();
  for(int i=0; i< xbin; i++){
    double x=hxa_1->GetBinContent(i);
    double a=hxa_1->GetXaxis()->GetBinCenter(i);
    //ofile1 << "0.010096920 " << x << " " << a << std::endl;
    ofile1 << "0.01 " << x << " " << a << std::endl;
  }
  ofile1.close();
  */
  
  TF1 *f = new TF1("f","pol1",-1.0,1.0);
  //TF1 *f = new TF1("f","pol3",-1.0,1.0);
  hxa_1->Fit("f");
  /*
  for(int i=0;i<5;i++){
    ofile2 << f->GetParameter(i) << " " ;
  }
  ofile2 << std::endl;
  ofile2.close();
  */
}
