
//run1040 delta=96.5%
{
  gROOT->LoadMacro("work/fp_las/CUTG/CUTG_delta96.5.C");
  ofstream ofile1("work/fp_las/dat/delta96.5.dat");
  ofstream ofile2("work/fp_las/fit/delta96.5_fit.dat");
  TFile *_file0 = TFile::Open("output/las/run1040.root");
  TH2F *hxa=new TH2F("hxa","LAS VDC x(mm) vs a(rad)",100,0,250,50,-0.125,0.18);
  tree->Draw("ldc.fA:ldc.GetX(605.319)>>hxa","CUTG","");
  hxa->FitSlicesX();
  gApplication->ProcessLine("gcom delta96.5 run1040");
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht hxa_1");
  int xbin=hxa_1->GetXaxis()->GetNbins();  
  for(int i=0; i< xbin; i++){
    double x=hxa_1->GetBinContent(i);
    double a=hxa_1->GetXaxis()->GetBinCenter(i);
    if(x != 0){
    ofile1 << "0.00 " << x << " " << a << std::endl;
    }
  }
  ofile1.close();
  TF1 *f = new TF1("f","pol3",-1.0,1.0);
  hxa_1->Fit("f","","");
  for(int i=0;i<4;i++){
    ofile2 << f->GetParameter(i) << " " ;
  }
  ofile2 << std::endl;
  ofile2.close();
}
