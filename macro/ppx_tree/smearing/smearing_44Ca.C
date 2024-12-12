void smearing_44Ca(void){
  TString infile="output/calib_pid/hist_ex/ppt_44Ca.root";
  TFile *file0 = TFile::Open(infile);

  
  TH1F* sx = (TH1F*)file0->Get("h_44Ca")->Clone("sx");
 
  
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
  
  int n_ave=21;
  //Double_t c[5]={1.0,1.0,1.0,1.0,1.0};
  Double_t sigma=0.4;//sqrt(0.38*0.38-0.25*0.25);
  Double_t c[21]={TMath::Gaus(-10*dx,0,sigma),
		  TMath::Gaus(-9*dx,0,sigma),
		  TMath::Gaus(-8*dx,0,sigma),
		  TMath::Gaus(-7*dx,0,sigma),
		  TMath::Gaus(-6*dx,0,sigma),
		  TMath::Gaus(-5*dx,0,sigma),
		  TMath::Gaus(-4*dx,0,sigma),
		  TMath::Gaus(-3*dx,0,sigma),
		  TMath::Gaus(-2*dx,0,sigma),
		  TMath::Gaus(-dx,0,sigma),
		  TMath::Gaus(0,0,sigma),
		  TMath::Gaus(dx,0,sigma),
		  TMath::Gaus(2*dx,0,sigma),
		  TMath::Gaus(3*dx,0,sigma),
		  TMath::Gaus(4*dx,0,sigma),
		  TMath::Gaus(5*dx,0,sigma),
		  TMath::Gaus(6*dx,0,sigma),
		  TMath::Gaus(7*dx,0,sigma),
		  TMath::Gaus(8*dx,0,sigma),
		  TMath::Gaus(9*dx,0,sigma),
		  TMath::Gaus(10*dx,0,sigma)};
  
  //int n_ave=4;
  //Double_t c[12]={1.0,1.0,1.0,1.0};


  TH1F *sx_smear=new TH1F("sx_smear", "",nBin,xMin,xMax);
  TH1F *sx_smear0=new TH1F("sx_smear0", "",nBin,xMin,xMax);

  
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
    sx_smear->SetBinContent( i+n_ave/2,val);
    sx_smear->SetBinError(i+n_ave/2,sqrt(err2)/c_sum);

    sx_smear0->SetBinContent( i+n_ave/2,val);
    sx_smear0->SetBinError(i+n_ave/2,0.0);    
  }

  //sx_smear->Rebin(4);
  //sx_smear0->Rebin(4);
  std::string ofile=infile.Data();
  ofile.resize(ofile.length() - 5);
  ofile += ".smeared.root";
  TFile *fout = new TFile((TString) ofile,"RECREATE");  
  sx_smear->Write();
  sx_smear0->Write();

  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht sx_smear");
  //sx_smear0->SetLineWidth(3);
  sx_smear0->Draw("same");

}
