{
  
  
  TFile *file = TFile::Open("output/ppx/momentum/ppt_carbon.2d.root");
  TFile *fout = new TFile("output/ppx/momentum/ppt_carbon.root","RECREATE");

  TH2F* gr_tc= (TH2F*) file->Get("gr_tc")->Clone();
  TH2F* gr_ac= (TH2F*) file->Get("gr_ac")->Clone();  
  
  TH1D *ht1 = gr_tc->ProjectionY("ht1",gr_tc->GetXaxis()->FindBin(145),gr_tc->GetXaxis()->FindBin(146.5));
  TH1D *ht2 = gr_tc->ProjectionY("ht2",gr_tc->GetXaxis()->FindBin(146.5),gr_tc->GetXaxis()->FindBin(148));
  TH1D *ht3 = gr_tc->ProjectionY("ht3",gr_tc->GetXaxis()->FindBin(148),gr_tc->GetXaxis()->FindBin(149.5));
  TH1D *ht4 = gr_tc->ProjectionY("ht4",gr_tc->GetXaxis()->FindBin(149.5),gr_tc->GetXaxis()->FindBin(151));
  TH1D *ht = gr_tc->ProjectionY("ht",gr_tc->GetXaxis()->FindBin(145),gr_tc->GetXaxis()->FindBin(149));
  ht->Scale(1.5/4.0); 
  
  
  TH1D *ha1 = gr_ac->ProjectionY("ha1",gr_ac->GetXaxis()->FindBin(145.5),gr_ac->GetXaxis()->FindBin(147));
  TH1D *ha2 = gr_ac->ProjectionY("ha2",gr_ac->GetXaxis()->FindBin(147),gr_ac->GetXaxis()->FindBin(148.5));
  TH1D *ha3 = gr_ac->ProjectionY("ha3",gr_ac->GetXaxis()->FindBin(148.5),gr_ac->GetXaxis()->FindBin(150));
  TH1D *ha4 = gr_ac->ProjectionY("ha4",gr_ac->GetXaxis()->FindBin(150),gr_ac->GetXaxis()->FindBin(151.5));
  TH1D *ha = gr_ac->ProjectionY("ha",gr_ac->GetXaxis()->FindBin(145),gr_ac->GetXaxis()->FindBin(149));
  ha->Scale(1.5/5.0); 
  
  int nBin=ht1->GetXaxis()->GetNbins();
  int xMin=ht1->GetXaxis()->GetXmin();
  int xMax=ht1->GetXaxis()->GetXmax();

  
  TH1D *h1=new TH1D("h1","h1",nBin,xMin,xMax);
  TH1D *h2=new TH1D("h2","h2",nBin,xMin,xMax);
  TH1D *h3=new TH1D("h3","h3",nBin,xMin,xMax);
  TH1D *h4=new TH1D("h4","h4",nBin,xMin,xMax);
  TH1D *h=new TH1D("h","h",nBin,xMin,xMax);
  
  h1->Add(ht1,1);
  h2->Add(ht2,1);
  h3->Add(ht3,1);
  h4->Add(ht4,1);
  h->Add(ht,1);

  h1->Add(ha1,-1);
  h2->Add(ha2,-1);
  h3->Add(ha3,-1);
  h4->Add(ha4,-1);
  h->Add(ha,-1);
  
  h1->Rebin(4);
  h2->Rebin(4);
  h3->Rebin(4);
  h4->Rebin(4);
  h->Rebin(4);

  //fout->Add(h1);
  //fout->Add(h2);
  //fout->Add(h3);
  //fout->Add(h4);

  h1->Write();
  h2->Write();
  h3->Write();
  h4->Write();
  h->Write();
}
