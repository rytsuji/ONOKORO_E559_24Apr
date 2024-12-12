{


  ofstream ofile("work/Li_ppt_chk/dat/ppt_kf0.dat");  
  TFile *_file0 = TFile::Open("output/chk/run2020.root");

  gROOT->LoadMacro("work/Li_ppt_chk/CUTG/CUTG_ppt_kf0.C");
  TH2F *h_gr_las = new TH2F("h_gr_las","Xfp GR vs LAS",110,-600,500,1000,-1000,1000);
  tree->Draw("vdc_las.GetX(32):vdc_gr.GetX(32)>>h_gr_las","CUTG","colz");
  h_gr_las->FitSlicesY();
  int xbin=h_gr_las_1->GetXaxis()->GetNbins();
  for(int i=0; i< xbin; i++){
    
    double x_las=h_gr_las_1->GetBinContent(i);
    double x_gr=h_gr_las_1->GetXaxis()->GetBinCenter(i);
    if(x_gr>-550){
      ofile << x_gr << " " << x_las << std::endl;
    }
  }

  ofile.close();

}
