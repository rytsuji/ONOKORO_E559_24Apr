
//run1036 delta=107%
{

  gROOT->LoadMacro("work/fp_las/TCutG_1037_las.C");
  ofstream ofile1("work/fp_las/dat/delta107.dat");
  ofstream ofile2("work/fp_las/fit/delta107_fit.dat");
  TFile *_file0 = TFile::Open("output/las/run1037.root");
  TH2F *hxa=new TH2F("hxa","LAS VDC x(mm) vs a(rad)",200,-350,-250,50,-0.21,0.15);
  tree->Draw("ldc.fA:ldc.fX>>hxa","CUTG","colz");
  hxa->FitSlicesX();
  gApplication->ProcessLine("gcom delta107 run1037");
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht hxa_1");
  int xbin=hxa_1->GetXaxis()->GetNbins();  
  for(int i=0; i< xbin; i++){
    double x=hxa_1->GetBinContent(i);
    double a=hxa_1->GetXaxis()->GetBinCenter(i);
    ofile1 << "0.07 " << x << " " << a << std::endl;
  }
  ofile1.close();
  TF1 *f = new TF1("f","pol5",-1.0,1.0);
  hxa_1->Fit("f");
  for(int i=0;i<6;i++){
    ofile2 << f->GetParameter(i) << " " ;
  }
  ofile2 << std::endl;
  ofile2.close();
}

