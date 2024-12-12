int MergeTree(std::string  reaction,std::string  target){

  TChain *tree= new TChain("tree", "");
  //read runlist
  std::vector<std::string> run;
  ifstream runlist(Form("runlist/%s/runlist_%s.txt",reaction.c_str(),target.c_str()));
  std::string line_runlist;  
  while(getline(runlist,line_runlist)){
    run.push_back(line_runlist);
  }


  const int n_file = run.size();
  
  
  
  for(int i=0;i<n_file;i++){


    std::cout << "***** processing run"  << run[i]  << " *****" <<std::endl;         
    tree->Add(Form("output/calib_pid/run%s.root",run[i].c_str()));
    //TFile *file_phys= TFile::Open(Form("output/hist_phys/run%s.hist.root",run[i].c_str));
  }

  TFile *chain = new TFile(Form("output/merge_calib/%s_%s.root",reaction.c_str(),target.c_str()),"RECREATE");
  tree->Write();
  chain->Close();
  return 0;
  
}
