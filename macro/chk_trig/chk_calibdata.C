void chk_calibdata(TString path_runlist){

  //read runlist
  ifstream runlist(path_runlist);
  std::string run;
  while(getline(runlist,run)){
    std::cout << "-----------run"  << run << "-----------" << std::endl; 
    TFile *file0= TFile::Open(Form("output/raw/run%s.root",run.c_str()));
    TFile *file1= TFile::Open(Form("output/calib/run%s.root",run.c_str()));      
    TTree* tr0=(TTree*)file0->Get("tree");
    TTree* tr1=(TTree*)file1->Get("tree");
    std::cout << "Entries  calib/raw  :" << (double) tr1->GetEntries("")/tr0->GetEntries("") << std::endl;
  }
  
}


