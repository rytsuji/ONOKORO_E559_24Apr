
//run1033 delta=100%
{
  gROOT->LoadMacro("work/fp_las/CUTG/CUTG_delta100.C");
  ofstream ofile1("work/fp_las/dat/delta100.dat");
  ofstream ofile2("work/fp_las/fit/delta100_fit.dat");
  TFile *_file0 = TFile::Open("output/las/run1033.root");
  TH2F *hxa=new TH2F("hxa","LAS VDC x(mm) vs a(rad)",100,-140,100,50,-0.15,0.15);
  TH2F *hxa_slice=new TH2F("hxa_slice","LAS VDC x(mm) vs a(rad)",100,-140,100,50,-0.15,0.15);  

  tree->Draw("ldc.fA:ldc.fX>>h(500,-1000,1000,500,-0.15,0.15)","","colz");
  tree->Draw("ldc.fA:ldc.GetX(605.319)>>hxa","CUTG","");
  hxa->FitSlicesX();
  gApplication->ProcessLine("gcom delta100 run1033");
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht hxa_1");
  int xbin=hxa_1->GetXaxis()->GetNbins();  
  for(int i=0; i< xbin; i++){
    double x=hxa_1->GetBinContent(i);
    double a=hxa_1->GetXaxis()->GetBinCenter(i);
    if(x != 0){
      ofile1 << "0.00 " << x << " " << a << std::endl;
      hxa_slice->Fill(x,a);
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
  hxa_slice->SetMarkerColor(2);
}
