//run1036 delta=101%
{

  double xc=229.765;//from work/ang_gr/dat
  TCut xcut=Form("abs(gfp.fX-%e)<10",xc);
  
  ofstream ofile1("work/tof_gr/dat/delta101.dat");
  ofstream ofile2("work/tof_gr/fit/delta101_fit.dat");

  TFile *_file0 = TFile::Open("output/gr/run1036.root");
  TH2F *hxt=new TH2F("hxt","GR TOF vs a_fp(rad)",250,-0.025,0.055,250,-350,-250);

  tree->Draw("pla_gr_1.fTiming-rf1.fTiming:gdc.fA>>hxt",xcut,"");
  hxt->FitSlicesY();

  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("gcom delta101 run1036");
  gApplication->ProcessLine("ht hxt_1");
  
  int Nbin=hxt_1->GetXaxis()->GetNbins();  
  for(int i=0; i< Nbin; i++){
    double x=hxt_1->GetBinContent(i);
    double t=hxt_1->GetXaxis()->GetBinCenter(i);
    ofile1 << "0.00 " << x << " " << t << std::endl;
  }
  ofile1.close();


  TF1 *f = new TF1("f","pol2",-1.0,1.0);
  hxt_1->Fit("f","","");
      ofile2 << xc << " " ;
  for(int i=0;i<3;i++){
    ofile2 << f->GetParameter(i) << " " ;
  }
  ofile2 << std::endl;  
  ofile2.close();
}

