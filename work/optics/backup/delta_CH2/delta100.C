{


  ofstream ofile("work/delta_CH2/dat/delta100.dat");
  
  TFile *_file0 = TFile::Open("output/chk/run1044.root");

  gROOT->LoadMacro("work/delta_CH2/CUTG/CUTG_delta100.C");
  TH2F *h_gr_las = new TH2F("h_gr_las","Xfp GR vs LAS",250,-310,225,1000,-1000,1000);
  tree->Draw("lfp.fX:gfp.fX>>h_gr_las","CUTG","colz");
  h_gr_las->FitSlicesY();
  int xbin=h_gr_las_1->GetXaxis()->GetNbins();
  for(int i=0; i< xbin; i++){
    
    double x_las=h_gr_las_1->GetBinContent(i);
    double x_gr=h_gr_las_1->GetXaxis()->GetBinCenter(i);
    if(x_gr>-300){
      ofile << x_gr << " " << x_las << std::endl;
    }
  }

  ofile.close();

}
