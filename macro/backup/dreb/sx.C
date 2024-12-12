{
  const int n_file=3; //number of input files
  TString file_root[n_file]={"run2070.hist.root","run2079.hist.root","run2117.hist.root"};

  double scale=-1.0/8.0; //scale of accidental coincidence
  
  TFile *file[n_file];
  TDirectoryFile* dir[n_file];
  TH1F* ht[n_file];
  TH1F* ha[n_file];
  TString dir_root="output/hist_phys/";
  
  
  for(int i=0;i<n_file;i++){  
    file[i] = TFile::Open(dir_root+file_root[i]);
    dir[i] = (TDirectoryFile*)file[i]->Get("phys");
    ht[i] = (TH1F*)dir[i]->Get("sx");
    ha[i] = (TH1F*)dir[i]->Get("sx_ac");
  }
  
  int nBin=ht[0]->GetXaxis()->GetNbins();
  int xMin=ht[0]->GetXaxis()->GetXmin();
  int xMax=ht[0]->GetXaxis()->GetXmax();
  TH1F *sx_tc=new TH1F("sx_tc", "",nBin,xMin,xMax);
  TH1F *sx_ac=new TH1F("sx_ac", "",nBin,xMin,xMax);
  TH1F *sx=new TH1F("sx", "sx",nBin,xMin,xMax);
  
  for(int i=0;i<n_file;i++){
    sx_tc->Add(ht[i],1.0);
    sx_ac->Add(ha[i],1.0);   
  }

  sx->Add(sx_tc,1.0);
  sx->Add(sx_ac,scale);
  sx_ac->Scale(-scale);
  
  sx_tc->Sumw2(0);
  sx_ac->Sumw2(0);
  sx_ac->SetLineColor(2);

  TCanvas *c1 =new TCanvas("c1","c1",800,600);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  
  sx_tc->SetStats(0);
  sx_ac->SetStats(0);

  sx_tc->SetTitle("");
  sx_tc->GetXaxis()->SetTitle("");
  sx_tc->GetYaxis()->SetTitle("");

  sx_tc->Rebin(2);
  sx_ac->Rebin(2);
  
  sx_tc->Draw();
  sx_ac->Draw("same");

  TLatex xtitle;
  xtitle.SetTextAlign(22);
  xtitle.SetNDC(1);
  xtitle.SetTextAngle(0);
  xtitle.DrawLatex(0.5,0.05,"#scale[0.8]{Separation energy #it{S_{X}} (MeV)}");
  
  TLatex ytitle;
  ytitle.SetTextAlign(11);
  ytitle.SetNDC(1);
  ytitle.SetTextAngle(90);
  ytitle.DrawLatex(0.05,0.5,"#scale[0.8]{count}");


  TLatex label;
  label.SetTextAlign(22);
  label.SetNDC(1);
  
  l1=new TLine(0.6,0.7,0.65,0.7);
  l1->SetNDC(1);
  l1->SetLineColor(4);
  l1->SetLineWidth(3);
  l1->Draw();
  label.DrawLatex(0.775,0.7,"#scale[0.65]{true coincidence}");
  
  l2=new TLine(0.6,0.65,0.65,0.65);
  l2->SetNDC(1);
  l2->SetLineColor(2);
  l2->SetLineWidth(3);
  l2->Draw();
  label.DrawLatex(0.775,0.65,"#scale[0.65]{accidental coincidence}");
  
}
