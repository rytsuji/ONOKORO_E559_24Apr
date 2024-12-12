{


  ofstream ofile("work/Li_ppt/dat/ppt_kfn.dat");  
  TFile *_file0 = TFile::Open("output/chk/run2022.root");

  gROOT->LoadMacro("work/Li_ppt/CUTG/CUTG_ppt_kfn.C");
  TH2F *h_gr_las = new TH2F("h_gr_las","Xfp GR vs LAS",75,-550,550,1000,-1000,1000);
  tree->Draw("lfp.fX:gfp.fX>>h_gr_las","CUTG","colz");
  h_gr_las->FitSlicesY();
  int xbin=h_gr_las_1->GetXaxis()->GetNbins();
  for(int i=0; i< xbin; i++){
    
    double x_las=h_gr_las_1->GetBinContent(i);
    double x_gr=h_gr_las_1->GetXaxis()->GetBinCenter(i);
    if(x_gr>-500 && fabs(h_gr_las_2->GetBinContent(i))<20){
      ofile << x_gr << " " << x_las << std::endl;
    }
  }

  ofile.close();

}
