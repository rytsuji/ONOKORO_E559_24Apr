{
  const int n_file=9; //number of input files
  TString file_root[n_file]={"run2086.hist.root","run2095.hist.root","run2127.hist.root","run2129.hist.root","run2132.hist.root","run2133.hist.root","run2134.hist.root","run2189.hist.root","run2190.hist.root"};

  double scale=-1.0/8.0; //scale of accidental coincidence
  
  TFile *file[n_file];
  TDirectoryFile* dir[n_file];
  TH1F* ht[n_file];
  TH1F* ha[n_file];
  TString dir_root="output/hist_phys/";
  
  
  for(int i=0;i<n_file;i++){  
    file[i] = TFile::Open(dir_root+file_root[i]);
    dir[i] = (TDirectoryFile*)file[i]->Get("40CaTp");
    ht[i] = (TH1F*)dir[i]->Get("TpL0_tc");
    ha[i] = (TH1F*)dir[i]->Get("TpL0_ac");
  }
  
  int nBin=ht[0]->GetXaxis()->GetNbins();
  int xMin=ht[0]->GetXaxis()->GetXmin();
  int xMax=ht[0]->GetXaxis()->GetXmax();
  TH1F *tp_tc=new TH1F("tp_tc", "true coin",nBin,xMin,xMax);
  TH1F *tp_ac=new TH1F("tp_ac", "accidental coin",nBin,xMin,xMax);
  TH1F *tp=new TH1F("tp", "tp",nBin,xMin,xMax);
  
  for(int i=0;i<n_file;i++){
    tp_tc->Add(ht[i],1.0);
    tp_ac->Add(ha[i],1.0);   
  }

  tp->Add(tp_tc,1.0);
  tp->Add(tp_ac,scale);
  
}
