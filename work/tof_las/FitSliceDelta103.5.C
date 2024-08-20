//run1033 delta=100%
{

  double xc=-155.0;
  TCut xcut=Form("abs(lfp.fX-(%e))<10",xc);
  
  ofstream ofile1("work/tof_las/dat/delta103.5.dat");
  ofstream ofile2("work/tof_las/fit/delta103.5_fit.dat");
  
  TFile *_file0 = TFile::Open("output/las/run1036.root");
  TH2F *hat=new TH2F("hat","LAS TOF vs a_fp(rad)",50,-0.18,0.17,100,380,480);
  TH2F *hat_slice=new TH2F("hat_slice","LAS TOF vs a_fp(rad)",1000,-0.18,0.17,1000,425,431);
  
  tree->Draw("pla_las_3.fTiming-rf1.fTiming:ldc.fA>>hat",xcut,"");
  hat->FitSlicesY();
  
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("gcom delta100 run1036");
  gApplication->ProcessLine("ht hat_1");
  
  int Nbin=hat_1->GetXaxis()->GetNbins();  
  for(int i=0; i< Nbin; i++){
    double a=hat_1->GetBinContent(i);
    double t=hat_1->GetXaxis()->GetBinCenter(i);
    double sigma_t=hat_2->GetXaxis()->GetBinCenter(i);    
    //std::cout << sigma_t << std::endl;
    if(t != 0 && sigma_t<0.2 ){
      hat_slice->Fill(t,a);
      ofile1 << "0.00 " << a << " " << t << std::endl;
    }
  }
  ofile1.close();
  

  hat_slice->SetMarkerStyle(8);
  TF1 *f = new TF1("f","pol1",-1.0,1.0);
  hat_slice->Fit("f","","");
  ofile2 << xc << " " ;
  for(int i=0;i<2;i++){
    ofile2 << f->GetParameter(i) << " " ;
  }
  ofile2 << std::endl;  
  ofile2.close();
}

