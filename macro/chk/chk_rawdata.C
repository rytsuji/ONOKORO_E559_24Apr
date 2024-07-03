void chk_rawdata(TString path_runlist){

  //
  //read runlist
  ifstream runlist(path_runlist);
  std::string run;
  while(getline(runlist,run)){
    std::cout << "-----------run"  << run << "-----------" << std::endl; 
    TFile *file= TFile::Open(Form("output/raw/run%s.root",run.c_str()));  
    TTree* tr=(TTree*)file->Get("tree");
    std::cout << "Entries coin trig :" <<tr->GetEntries("trig_coin.fID==0") << std::endl;
    std::cout << "Scaler  coin trig :" << ScaData(std::stoi(run),15) << std::endl;
  }


  
}


