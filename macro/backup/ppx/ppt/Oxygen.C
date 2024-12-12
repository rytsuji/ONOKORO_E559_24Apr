{
  const int n_file=2; //number of input files
  TString file_root[n_file]={"run2079.hist.root","run2080.hist.root"};
  double scale_bg=1.0/8.0; //scale of accidental coincidence
  
  TFile *file[n_file];
  TDirectoryFile* dir[n_file];
  TH1F* ht[n_file];
  TH1F* ha[n_file];
  TString dir_root="output/phys/";
  
  
  for(int i=0;i<n_file;i++){  
    file[i] = TFile::Open(dir_root+file_root[i]);
    dir[i] = (TDirectoryFile*)file[i]->Get("phys");
    ht[i] = (TH1F*)dir[i]->Get("sx");
    ha[i] = (TH1F*)dir[i]->Get("sx_ac");
  }
  
  int nBin=ht[0]->GetXaxis()->GetNbins();
  int xMin=ht[0]->GetXaxis()->GetXmin();
  int xMax=ht[0]->GetXaxis()->GetXmax();
  TH1F *sx_c=new TH1F("sx_c", "",nBin,xMin,xMax);
  TH1F *sx_m=new TH1F("sx_m", "",nBin,xMin,xMax);

  sx_c->Add(ht[0],1);
  sx_c->Add(ha[0],-1.0/8.0);

  Double_t BI0=1.3260702*0.25*( ScaData(2079,28)+ScaData(2079,29)+ScaData(2079,30)+ScaData(2079,31) );
  Double_t BI1=1.3260702*0.25*( ScaData(2080,28)+ScaData(2080,29)+ScaData(2080,30)+ScaData(2080,31) );
  
  Double_t scale=0.66348429;//*(48.0080/10.47)/(12.0/10.65);
  sx_c->Scale(BI1/BI0*scale);
  sx_c->SetLineColor(2);
  sx_c->Sumw2(0);

  sx_m->Add(ht[1],1);
  sx_m->Add(ha[1],-1.0/8.0);
  sx_m->Sumw2(0);
}
