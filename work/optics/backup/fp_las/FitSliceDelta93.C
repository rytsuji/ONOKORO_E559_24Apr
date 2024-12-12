
//run1036 delta=103.5%
{

  gROOT->LoadMacro("work/fp_las/TCutG_1041_las.C");
  ofstream ofile1("work/fp_las/dat/delta93.dat");
  ofstream ofile2("work/fp_las/fit/delta93_fit.dat");
  TFile *_file0 = TFile::Open("output/las/run1041.root");
  TH2F *hxa=new TH2F("hxa","LAS VDC x(mm) vs a(rad)",200,280,380,40,-0.1,0.21);
  tree->Draw("ldc.fA:ldc.fX>>hxa","CUTG","colz");
  hxa->FitSlicesX();
  gApplication->ProcessLine("gcom delta93 run1041");
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht hxa_1");
  int xbin=hxa_1->GetXaxis()->GetNbins();  
  for(int i=0; i< xbin; i++){
    double x=hxa_1->GetBinContent(i);
    double a=hxa_1->GetXaxis()->GetBinCenter(i);
    ofile1 << "-0.07 " << x << " " << a << std::endl;
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

