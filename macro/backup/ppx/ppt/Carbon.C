{
  std::string  reaction="ppt";
  std::string  target="carbon";
  std::vector<std::string> run;
  ifstream runlist(Form("runlist/%s/runlist_%s.txt",reaction.c_str(),target.c_str()));
  std::string line_runlist;
  while(getline(runlist,line_runlist)){
    run.push_back(line_runlist);
  }
  /*
  const int n_file = run.size();

  TH1F* ht[n_file];
  TH1F* ha[n_file];
  */

  TH1F* ht[3];
  TH1F* ha[3];

  for(int i=0;i<run.size();i++){
    std::cout << "processing run"  << run[i]  << std::endl;
    TFile *file_phys= TFile::Open(Form("output/hist_phys/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_phys=(TDirectoryFile*)file_phys->Get("phys");
    ht[i] = (TH1F*)dir_phys->Get("sx");
    ha[i] = (TH1F*)dir_phys->Get("sx_ac");    
  }

  int nBin=ht[0]->GetXaxis()->GetNbins();
  int xMin=ht[0]->GetXaxis()->GetXmin();
  int xMax=ht[0]->GetXaxis()->GetXmax();

  TH1F *h1=new TH1F("h1", "",nBin,xMin,xMax);
  TH1F *h2=new TH1F("h2", "",nBin,xMin,xMax);
  TH1F *h3=new TH1F("h3", "",nBin,xMin,xMax);

  h1->Add(ht[0],1.0);
  h1->Add(ha[0],-1.0/8.0);
  h1->Rebin(4);
  h1->Scale(1.0/(double)h1->GetEntries());
  h1->Sumw2(0);
  
  h2->Add(ht[1],1.0);
  h2->Add(ha[1],-1.0/8.0);
  h2->Rebin(4);
  h2->Scale(1.0/(double)h2->GetEntries());
  h2->Sumw2(0);
  
  h3->Add(ht[2],1.0);
  h3->Add(ha[2],-1.0/8.0);
  h3->Rebin(4);
  h3->Scale(1.0/(double)h3->GetEntries());
  h3->Sumw2(0);
}


