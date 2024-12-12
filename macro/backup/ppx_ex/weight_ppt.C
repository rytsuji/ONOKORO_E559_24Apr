void weight_ppt(TString infile,double St){
  
  TFile *file0 = TFile::Open(infile);  
  TH1F* sx = (TH1F*)file0->Get("sx");

  Double_t Sx[4]={7.98,15.98,28.98,36.98};
  Double_t dTp=8.0;
  
  
  int nBin=sx->GetXaxis()->GetNbins();
  double xMin=sx->GetXaxis()->GetXmin();
  double xMax=sx->GetXaxis()->GetXmax();

  Double_t *BinContents_sx = new Double_t[nBin];
  Double_t *BinError_sx = new Double_t[nBin];
  
  for(int i=0;i<nBin;i++){
    BinContents_sx[i]=sx->GetBinContent(i);
    BinError_sx[i]=sx->GetBinError(i);
  }


  Double_t dx=(xMax-xMin)/(double)nBin;
  
  int n_ave=1;
  //Double_t c[5]={1.0,1.0,1.0,1.0,1.0};
  Double_t c[1]={1.0};
  //Double_t c[5]={TMath::Gaus(-2*dx,0,0.19),
  //TMath::Gaus(-dx,0,0.19),
  //TMath::Gaus(0,0,0.19),
  //TMath::Gaus(2*dx,0,0.19),
  //TMath::Gaus(dx,0,0.19)};
  
  //int n_ave=4;
  //Double_t c[12]={1.0,1.0,1.0,1.0};


  TH1F *sx_weight=new TH1F("sx_weight", "",nBin,xMin,xMax);
  TH1F *sx_weight0=new TH1F("sx_weight0", "",nBin,xMin,xMax);

  
  for(int i= 0;i < nBin;i++){

    Double_t scale=1.0;
    Double_t val=0;
    Double_t err=0;

    Double_t SxVal=(xMax-xMin)*(((Double_t) i+0.5)/(Double_t) nBin)+xMin+St;
    
    if(SxVal<=Sx[0]){
      scale=1.0;
    }else if(SxVal<=Sx[1]){
      scale=dTp/(SxVal-Sx[0]);
    }else if(SxVal<=Sx[2]){
      scale=1.0;
    }else if(SxVal<Sx[3]-1.0){
      scale=dTp/(Sx[3]-SxVal);
    }else{
      scale=1.0;
    }
    
    val+=BinContents_sx[i];
    err+=BinError_sx[i];
  
    sx_weight->SetBinContent( i,val*scale);
    sx_weight->SetBinError(i,err*scale);

    sx_weight0->SetBinContent(i,val*scale);
    sx_weight0->SetBinError(i,0.0);    
  }

  sx_weight->SetLineColor(2);
  sx_weight->SetMarkerColor(2);
  sx_weight0->SetLineColor(2);
  sx_weight0->SetMarkerColor(2);

  //sx_weight->Rebin(16);
  //sx_weight0->Rebin(16);
  //sx_weight->Rebin(20);
  //sx_weight0->Rebin(20);
  std::string ofile=infile.Data();
  ofile.resize(ofile.length() - 5);
  ofile += ".weight.root";
  TFile *fout = new TFile((TString) ofile,"RECREATE");  
  sx_weight->Write();
  sx_weight0->Write();

  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht sx_weight");
  //sx_weight0->SetLineWidth(3);
  sx_weight0->Draw("same");

}
