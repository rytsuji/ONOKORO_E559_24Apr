

void hist_ac(std::string  reaction,std::string  target){

  
  //read runlist
  std::vector<std::string> run;
  ifstream runlist(Form("runlist/%s/runlist_%s.txt",reaction.c_str(),target.c_str()));
  std::string line_runlist;  
  while(getline(runlist,line_runlist)){
    run.push_back(line_runlist);
  }


  const int n_file = run.size();
  TH1F* hac[n_file];
  
  for(int i=0;i<run.size();i++){
    std::cout << "processing run"  << run[i]  << std::endl;         
    

    TFile *file_phys= TFile::Open(Form("output/hist_phys/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_phys=(TDirectoryFile*)file_phys->Get("phys");  
    hac[i] = (TH1F*)dir_phys->Get("tof_ac");
    //hac[i]->Sumw2(0);
  }



  
  int nBin=hac[0]->GetXaxis()->GetNbins();
  int xMin=hac[0]->GetXaxis()->GetXmin();
  int xMax=hac[0]->GetXaxis()->GetXmax();

  TH1F *tof_ac=new TH1F("tof_ac", "acc coin",nBin,xMin,xMax);
  tof_ac->Sumw2(0);
  for(int i=0;i<n_file;i++){
    tof_ac->Add(hac[i],1.0);
  }
  gApplication->ProcessLine("ht tof_ac");
}


