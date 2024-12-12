int baseline(TString file){

  TFile *file0 = TFile::Open(file);
  TH1F* sx = (TH1F*)file0->Get("sx");
  TH1F* sx_tc = (TH1F*)file0->Get("sx_tc");
  TH1F* sx_ac = (TH1F*)file0->Get("sx_ac");

  //sx->Rebin(5);
  //sx_tc->Rebin(5);
  //sx_ac->Rebin(5);
  
  TH1F* hbl = new TH1F("hbl","hbl",200,-0.02,0.02);
  //TH1F* hbl_tc = new TH1F("hbl_tc","hbl_tc",100,-0.02,0.02);
  //TH1F* hbl_ac = new TH1F("hbl_ac","hbl_ac",100,-0.02,0.02);
  //TH2F* hbl_tc_ac = new TH2F("hbl_tc_ac","hbl_tc_ac",1000,0,100,1000,0,100);


  double range[2]={-15.0,-2.5};
  int minBin=sx->FindBin(range[0]);
  int maxBin=sx->FindBin(range[1]);

  for(int i=minBin;i<=maxBin;i++){
    double BinVal_sx=sx->GetBinContent(i);
    double BinVal_sx_tc=sx_tc->GetBinContent(i);
    double BinVal_sx_ac=sx_ac->GetBinContent(i);
    hbl->Fill(BinVal_sx);
    //hbl_tc->Fill(BinVal_sx_tc);
    //hbl_ac->Fill(BinVal_sx_ac);
    //hbl_tc_ac->Fill(BinVal_sx_tc,BinVal_sx_ac);           
  }
  return 0;
}
