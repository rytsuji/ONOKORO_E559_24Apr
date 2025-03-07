void smearing(TString infile){
  
  TFile *file0 = TFile::Open(infile);

  
  TH1F* sx_raw = (TH1F*)file0->Get("sx");
  
  
  int nBin=sx_raw->GetXaxis()->GetNbins();
  double xMin=sx_raw->GetXaxis()->GetXmin();
  double xMax=sx_raw->GetXaxis()->GetXmax();
  
  Double_t *BinContents_sx = new Double_t[nBin];
  Double_t *BinError_sx = new Double_t[nBin];
  
  for(int i=0;i<nBin;i++){
    BinContents_sx[i]=sx_raw->GetBinContent(i);
    BinError_sx[i]=sx_raw->GetBinError(i);
  }
  

  Double_t dx=(xMax-xMin)/(double)nBin;
  
  const int n_smearing=5;
  //Double_t sigma=0.2;//ppt
  Double_t sigma=0.4;//pph  

  Double_t c[n_smearing];
  for(int i=0; i<n_smearing; i++){
    c[i]=TMath::Gaus(dx*((Double_t) (i-(int)n_smearing/2)),0,sigma);     
  }
  



  TH1F *sx_smear=new TH1F("sx_smear", "",nBin,xMin,xMax);
  TH1F *sx_smear0=new TH1F("sx_smear0", "",nBin,xMin,xMax);

  
  for(int i= 0;i < nBin - 2*(n_smearing/2);i++){

    Double_t val=0;
    Double_t err2=0;
    Double_t c_sum=0;
    for(int j=0;j<n_smearing;j++){
      val+=c[j]*BinContents_sx[i+j];
      err2+=pow(c[j]*BinError_sx[i+j],2.0);
      c_sum+=c[j];
    }
    val = val/c_sum;    
    sx_smear->SetBinContent( i+n_smearing/2,val);
    sx_smear->SetBinError(i+n_smearing/2,sqrt(err2)/c_sum);

    sx_smear0->SetBinContent( i+n_smearing/2,val);
    sx_smear0->SetBinError(i+n_smearing/2,0.0);    
  }

  std::string ofile=infile.Data();
  ofile.resize(ofile.length() - 5);
  ofile += ".smeared.root";
  TFile *fout = new TFile((TString) ofile,"RECREATE");  
  sx_smear->Write();
  sx_smear0->Write();

  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht sx_smear");
  sx_smear0->Draw("same");

}
