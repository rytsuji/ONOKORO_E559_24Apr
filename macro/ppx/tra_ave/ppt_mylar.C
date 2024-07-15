{
  
  TFile *_file0 = TFile::Open("macro/ppx/output_sx/ppt_mylar.root");
  
  int nBin=sx->GetXaxis()->GetNbins();
  double xMin=sx->GetXaxis()->GetXmin();
  double xMax=sx->GetXaxis()->GetXmax();

  Double_t *BinContents_sx = new Double_t[nBin];
  Double_t *BinError_sx = new Double_t[nBin];
  
  for(int i=0;i<nBin;i++){
    BinContents_sx[i]=sx->GetBinContent(i);
    BinError_sx[i]=sx->GetBinError(i);
  }

  int n_ave=5;
  Double_t c[5]={1.0,1.0,1.0};

  //int n_ave=4;
  //Double_t c[12]={1.0,1.0,1.0,1.0};

  Double_t dx=(xMax-xMin)/(double)nBin;
  TH1F *sx_tave=new TH1F("sx_tave", "",nBin,xMin,xMax);
  TH1F *sx_tave0=new TH1F("sx_tave0", "",nBin,xMin,xMax);

  
  for(int i= 0;i < nBin - 2*(n_ave/2);i++){

    Double_t val=0;
    Double_t err2=0;
    Double_t c_sum=0;
    for(int j=0;j<n_ave;j++){
      val+=c[j]*BinContents_sx[i+j];
      err2+=pow(c[j]*BinError_sx[i+j],2.0);
      c_sum+=c[j];
    }
    val = val/c_sum;    
    sx_tave->SetBinContent( i+n_ave/2,val);
    sx_tave->SetBinError(i+n_ave/2,sqrt(err2)/c_sum);

    sx_tave0->SetBinContent( i+n_ave/2,val);
    sx_tave0->SetBinError(i+n_ave/2,0.0);    
  }

  sx_tave->Rebin(2);
  sx_tave0->Rebin(2);
  TFile *fout = new TFile("macro/ppx/output_sx/ppt_mylar_tave.root","RECREATE");  
  sx_tave->Write();
  sx_tave0->Write();
}
