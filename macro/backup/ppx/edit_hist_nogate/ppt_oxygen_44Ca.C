{

  double scale=1;
  TFile *file_mylar = TFile::Open("output/ppx_nogate/ppt_mylar.tra_ave.root ");  
  TFile *file_carbon = TFile::Open("output/ppx_nogate/ppt_carbon.tra_ave.root ");
  TFile *file_44Ca = TFile::Open("output/ppx_nogate/ppt_44Ca.tra_ave.root ");  
    
  Double_t ymin=-0.0099;
  Double_t ymax=0.0999;
  
  TH1F *h_mylar = (TH1F*)file_mylar->Get("sx_tave")->Clone("h_mylar");
  TH1F *h_mylar0 = (TH1F*)file_mylar->Get("sx_tave0")->Clone("h_mylar0");
  TH1F *h_carbon = (TH1F*)file_carbon->Get("sx_tave")->Clone("h_carbon");
  TH1F *h_carbon0 = (TH1F*)file_carbon->Get("sx_tave0")->Clone("h_carbon0");
  TH1F *h_oxygen = (TH1F*)file_mylar->Get("sx_tave")->Clone("h_oxygen");
  TH1F *h_oxygen0 = (TH1F*)file_mylar->Get("sx_tave0")->Clone("h_oxygen0");
  TH1F *h_44Ca = (TH1F*)file_44Ca->Get("sx_tave")->Clone("h_44Ca");
  TH1F *h_44Ca0 = (TH1F*)file_44Ca->Get("sx_tave0")->Clone("h_44Ca0");   
  
    
  //h_mylar->SetLabelSize(0.075*scale,"xy");
  //h_mylar->GetXaxis()->SetRange(sx_tave->FindBin(10),sx_tave->FindBin(45));
  
  h_44Ca->SetMinimum(ymin);
  h_44Ca->SetMaximum(ymax);
  
  Double_t scale_carbon=0.66348429*(48.0080/10.47)/(12.0/10.65);
  h_carbon->Scale(scale_carbon);
  h_carbon0->Scale(scale_carbon);
  h_carbon->SetLineColor(2);
  h_carbon0->SetLineColor(2);
  h_carbon0->SetMarkerColor(2);

  h_44Ca->SetLineColor(2);
  h_44Ca->SetMarkerColor(2);  
  h_44Ca0->SetLineColor(2);  
  h_44Ca0->SetMarkerColor(2);  
  //sx_tave->SetLabelSize(0.06,"y");
  
  h_mylar->SetStats(0);
  h_mylar0->SetStats(0);
  h_carbon->SetStats(0);
  h_carbon0->SetStats(0);
  h_oxygen->SetStats(0);
  h_oxygen0->SetStats(0);
  h_44Ca->SetStats(0);
  h_44Ca0->SetStats(0);
  
  h_oxygen->Add(h_carbon,-1.0);
  h_oxygen0->Add(h_carbon0,-1.0);  
  Double_t scale_oxygen_44Ca=(0.21808865/(9.7/43.955))*0.284;
  h_oxygen->Scale(scale_oxygen_44Ca);
  h_oxygen0->Scale(scale_oxygen_44Ca);  

  h_oxygen->Rebin(2);
  h_oxygen0->Rebin(2);
  h_44Ca->Rebin(2);
  h_44Ca0->Rebin(2);

  
  h_44Ca->Draw();
  h_44Ca0->Draw("same");  
  h_oxygen->Draw("same");
  h_oxygen0->Draw("same");  


  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  //  title.DrawLatex(.65,.8,Form("#scale[%f]{Mylar/^{12}C(#it{p,pt})}",1.0*scale));
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{44}Ca(#it{p,pt})}",1.0*scale));
  //title.DrawLatex(.65,.7,Form("#scale[%f]{^{44-48}O(#it{p,pt}) setup}",1.0*scale));  
  //title.DrawLatex(.65,.725,Form("#scale[%f]{#it{S_{t}}=24.996 MeV}",0.8*scale));

  Double_t St = 20.859;
  TLine *l[11];
  for(int i=0;i<11;i++){
    l[i]= new TLine(St+2*i,ymin,St+2*i,ymax);
    if( (i%5) == 0){
      l[i]->SetLineStyle(1);
    }else{
      l[i]->SetLineStyle(2);
    }
    l[i]->Draw("same");
  }  

}
