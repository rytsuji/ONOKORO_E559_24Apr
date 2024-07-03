{

  Double_t scale=0.66348429*(48.0080/10.47)/(12.0/10.65);
  
  TFile *file_mylar = TFile::Open("macro/ppx/output_sx/ppt_mylar.root");
  TFile *file_carbon = TFile::Open("macro/ppx/output_sx/ppt_carbon.root");
  
  int nBin=sx->GetXaxis()->GetNbins();
  double xMin=sx->GetXaxis()->GetXmin();
  double xMax=sx->GetXaxis()->GetXmax();

  TH1F* h_mylar_raw= (TH1F*) file_mylar->Get("sx")->Clone();
  h_mylar_raw->SetName("h_mylar_raw");
  TH1F* h_carbon_raw= (TH1F*) file_carbon->Get("sx")->Clone();
  h_carbon_raw->SetName("h_carbon_raw");
  //h_mylar_raw->Sumw2(0);
  //h_carbon_raw->Sumw2(0);
  
  Double_t *BinContents_mylar = new Double_t[nBin];
  Double_t *BinContents_carbon = new Double_t[nBin];

  Double_t *BinErr_mylar = new Double_t[nBin];
  Double_t *BinErr_carbon = new Double_t[nBin];

  
  for(int i=0;i<nBin;i++){
    BinContents_mylar[i]=h_mylar_raw->GetBinContent(i);
    BinContents_carbon[i]=h_carbon_raw->GetBinContent(i);
    BinErr_mylar[i]=h_mylar_raw->GetBinError(i);
    BinErr_carbon[i]=h_carbon_raw->GetBinError(i);
  }

  int n_ave=5;
  Double_t c[12]={1.0,1.0,1.0,1.0,
		  1.0,1.0,1.0,1.0,
		  1.0,1.0,1.0,1.0};

  TH1F *sx_carbon=new TH1F("sx_carbon", "",nBin,xMin,xMax);
  TH1F *sx_mylar=new TH1F("sx_mylar", "",nBin,xMin,xMax);
  TH1F *sx_oxygen=new TH1F("sx_oxygen", "",nBin,xMin,xMax);
  
  TH1F *sx_carbon0=new TH1F("sx_carbon0", "",nBin,xMin,xMax);
  TH1F *sx_mylar0=new TH1F("sx_mylar0", "",nBin,xMin,xMax);
  TH1F *sx_oxygen0=new TH1F("sx_oxygen0", "",nBin,xMin,xMax);


  for(int i= 0;i < nBin - n_ave ;i++){

    Double_t val_mylar=0;
    Double_t val_carbon=0;
    Double_t err_mylar2=0;
    Double_t err_carbon2=0;
    Double_t c_sum=0;

    for(int j=0;j<n_ave;j++){
      val_mylar+=c[j]*BinContents_mylar[i+j];
      val_carbon += c[j]*BinContents_carbon[i+j];
      err_mylar2 += pow(c[j]*BinErr_mylar[i+j],2.0);
      err_carbon2 += pow(c[j]*BinErr_carbon[i+j],2.0);
      c_sum += c[j];
    }
    
    val_mylar = val_mylar/c_sum;
    val_carbon = val_carbon/c_sum;    
    sx_mylar0->SetBinContent( i+n_ave/2,val_mylar);
    sx_mylar0->SetBinError(i+n_ave/2,0);
    sx_mylar->SetBinContent( i+n_ave/2,val_mylar);
    sx_mylar->SetBinError(i+n_ave/2,sqrt(err_mylar2)/c_sum);

    sx_carbon0->SetBinContent( i+n_ave/2,scale*val_carbon);
    sx_carbon0->SetBinError(i+n_ave/2,0);    
    sx_carbon->SetBinContent( i+n_ave/2,scale*val_carbon);
    sx_carbon->SetBinError(i+n_ave/2,sqrt(err_carbon2)/c_sum);    

    sx_oxygen0->SetBinContent( i+n_ave/2,val_mylar-scale*val_carbon);
    sx_oxygen0->SetBinError(i+n_ave/2,0);    
    sx_oxygen->SetBinContent( i+n_ave/2,val_mylar-scale*val_carbon);
    sx_oxygen->SetBinError(i+n_ave/2,sqrt(err_mylar2+scale*scale*err_carbon2)/c_sum);        
  }
  
  sx_mylar->Rebin(2);
  sx_carbon->Rebin(2);
  sx_oxygen->Rebin(2);

  sx_mylar0->Rebin(2);
  sx_carbon0->Rebin(2);
  sx_oxygen0->Rebin(2);

  
  TFile *fout = new TFile("macro/ppx/output_sx/ppt_16O_tave.root","RECREATE");
  sx_mylar->Write();
  sx_carbon->Write();
  sx_oxygen->Write();
  sx_mylar0->Write();
  sx_carbon0->Write();
  sx_oxygen0->Write();
}

