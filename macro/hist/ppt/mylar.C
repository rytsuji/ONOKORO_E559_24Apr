{
  Double_t scale=1.0;
  TFile *file0 = TFile::Open("output/calib_pid/hist_sx/ppt_mylar.root");

  //sx->Rebin(4);
  //sx0->Rebin(4);  
  
  TF1 *f = new TF1("f","([0]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[1])/[10],2))+([2]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[3])/[10],2))+([4]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[5])/[10],2))+([6]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[7])/[10],2))+([8]/sqrt(2.*TMath::Pi()*[10]*[10]))*exp(-0.5*pow((x-[9])/[10],2))",0.0,50.0);

  f->SetParName(0,"const1");
  f->SetParName(1,"mean1");
  f->SetParName(2,"const2");
  f->SetParName(3,"mean2");
  f->SetParName(4,"const3");
  f->SetParName(5,"mean3");
  f->SetParName(6,"const4");
  f->SetParName(7,"mean4");
  f->SetParName(8,"const5");
  f->SetParName(9,"mean5");
  f->SetParName(10,"sigma");
  //f->SetParName(6,"sigma");  
  //f->SetParName(8,"sigma");


  Double_t ymin=-0.02;
  Double_t ymax=0.60;
  sx->Rebin(4);
  sx0->Rebin(4);
  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);
  sx->GetXaxis()->SetRange(sx->FindBin(15),sx->FindBin(40));

  sx->SetStats(0);
  sx->SetTitle("");
  sx->GetXaxis()->SetTitle("#mbox{S_{X}} (MeV)");
  sx->GetXaxis()->CenterTitle(true);
  sx->GetYaxis()->CenterTitle(true);

  sx->Draw("E1");
  sx0->Draw("same");

  f->SetParameters(0.03,25.0,
		   0.15,27.5,
		   0.10,28.5,
		   0.01,29.0,
		   0.03,29.5,
		   0.185);
  sx->Fit("f","","",23,30);

  //f_16O=;
  //f_16O=;    
  
  TFile *file1 = TFile::Open("output/calib_pid/hist_sx/ppt_carbon.root");
  Double_t scale_carbon=0.66348429*(48.0080/10.47)/(12.0/10.65);
  sx->Rebin(4);  
  sx0->Rebin(4);
  sx->Scale(scale_carbon);
  sx0->Scale(scale_carbon);  
  sx0->Sumw2(0);
  sx->SetLineColor(3);
  sx->SetMarkerColor(3);
  sx0->SetLineColor(3);
  sx0->SetMarkerColor(3);  
  sx->Draw("E1 same");
  sx0->Draw("same");


  Double_t St0=25.032;
  Double_t y0=0.075;
  TArrow a0(St0,y0,St0,y0+0.02,0.01,"<|");
  a0.Draw();
  TLatex t0;
  t0.SetTextAlign(12);
  t0.SetTextAngle(90);
  t0.DrawLatex(St0,y0+0.03,Form("#scale[%f]{gnd (1/2^{-})}",scale*0.75));


  Double_t St1=28.532;
  Double_t y1=0.25;
  TArrow a1(St1,y1,St1,y1+0.02,0.01,"<|");
  a1.Draw();
  TLatex t1;
  t1.SetTextAlign(12);
  t1.SetTextAngle(90);
  t1.DrawLatex(St1,y1+0.03,Form("#scale[%f]{3.50 MeV (3/2^{-})}",scale*0.75));

  
  
}
