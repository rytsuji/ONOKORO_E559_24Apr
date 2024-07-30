
//run1033 delta=100%
{

  gROOT->LoadMacro("work/fp_las/TCutG_1033_las.C");
  ofstream ofile1("work/fp_las/itr/dat/delta100.dat");
  ofstream ofile2("work/fp_las/itr/fit/delta100_fit.dat");
  TFile *_file0 = TFile::Open("output/las/run1033.root");
  TH2F *hxa=new TH2F("hxa","LAS VDC x(mm) vs a(rad)",200,-50,50,40,-0.15,0.18);
  tree->Draw("ldc.fA:ldc.fX>>hxa","CUTG","colz");
  hxa->FitSlicesX();
  gApplication->ProcessLine("gcom delta100 run1033");
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht hxa_1");
  int xbin=hxa_1->GetXaxis()->GetNbins();  
  for(int i=0; i< xbin; i++){
    double x=hxa_1->GetBinContent(i);
    double a=hxa_1->GetXaxis()->GetBinCenter(i);
    ofile1 << "0.00 " << x << " " << a << std::endl;
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

