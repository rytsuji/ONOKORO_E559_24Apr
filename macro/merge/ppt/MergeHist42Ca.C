{
  const int n_file=8; //number of input files
  TString file_root[n_file]={"run2076.hist.root","run2084.hist.root","run2123.hist.root","run2124.hist.root","run2166.hist.root","run2167.hist.root","run2168.hist.root","run2169.hist.root"};

  double scale=1.0/12.0; //scale of accidental coincidence
  
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
  TH1F *sx_tc=new TH1F("sx_tc", "true coin",nBin,xMin,xMax);
  TH1F *sx_ac=new TH1F("sx_ac", "accidental coin",nBin,xMin,xMax);
  TH1F *sx=new TH1F("sx", "sx",nBin,xMin,xMax);
  
  for(int i=0;i<n_file;i++){
    sx_tc->Add(ht[i],1.0);
    sx_ac->Add(ha[i],1.0);   
  }

  sx_ac->Sumw2();
  sx_tc->Sumw2();
  sx_ac->Scale(scale);

  sx->Sumw2();
  sx->Add(sx_tc,1.0);  
  sx->Add(sx_ac,-1.0);
  
  
  TH1F *sx0=new TH1F("sx0", "sx0",nBin,xMin,xMax);
  sx0->Add(sx,1.0);
  sx0->Sumw2(0);

  //sx->Rebin(2);
  sx->GetXaxis()->ZoomOut(0.6,0.5);  

  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht sx E1");
  gApplication->ProcessLine("gcom 42Ca(p,pt) Merged");  


  //sx0->Rebin(2);
  sx0->Draw("same");
  sx_tc->Sumw2(0);
  sx_ac->Sumw2(0);
  sx_ac->SetLineColor(2);
}
