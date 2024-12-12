{

  double scale=1;
  TFile *file_mylar = TFile::Open("output/ppx_nogate/ppt_mylar.tra_ave.root ");  
  TFile *file_carbon = TFile::Open("output/ppx_nogate/ppt_carbon.tra_ave.root ");
    
  Double_t ymin=-0.0499;
  Double_t ymax=0.4999;
  
  TH1F *h_mylar = (TH1F*)file_mylar->Get("sx_tave")->Clone("h_mylar");
  TH1F *h_mylar0 = (TH1F*)file_mylar->Get("sx_tave0")->Clone("h_mylar0");
  TH1F *h_carbon = (TH1F*)file_carbon->Get("sx_tave")->Clone("h_carbon");
  TH1F *h_carbon0 = (TH1F*)file_carbon->Get("sx_tave0")->Clone("h_carbon0");   

  TH1F *h_oxygen = (TH1F*)file_mylar->Get("sx_tave")->Clone("h_oxygen");
  TH1F *h_oxygen0 = (TH1F*)file_mylar->Get("sx_tave0")->Clone("h_oxygen0");  
    
  h_mylar->SetLabelSize(0.075*scale,"xy");
  h_mylar->GetXaxis()->SetRange(sx_tave->FindBin(10),sx_tave->FindBin(45));
  
  h_mylar->SetMinimum(ymin);
  h_mylar->SetMaximum(ymax);
  
  Double_t scale_carbon=0.66348429*(48.0080/10.47)/(12.0/10.65);
  h_carbon->Scale(scale_carbon);
  h_carbon0->Scale(scale_carbon);
  h_carbon->SetLineColor(2);
  h_carbon0->SetLineColor(2);
  h_carbon0->SetMarkerColor(2);

  
  //sx_tave->SetLabelSize(0.06,"y");
  
  h_mylar->SetStats(0);
  h_mylar0->SetStats(0);
  h_carbon->SetStats(0);
  h_carbon0->SetStats(0);

  h_oxygen->SetStats(0);
  h_oxygen0->SetStats(0);  

  h_oxygen->Add(h_carbon,-1.0);
  h_oxygen0->Add(h_carbon0,-1.0);  

  h_oxygen->Draw();
  h_oxygen0->Draw("same");  
  
  //h_mylar->Draw();
  //h_mylar0->Draw("same");
  //h_carbon->Draw("same");
  //h_carbon0->Draw("same");
  
  Double_t St_16O=25.032;
  TLatex t_16O;
  t_16O.SetTextAlign(12);
  t_16O.SetTextAngle(90);
  
  Double_t E1_16O=2.3649;
  Double_t y0_16O=0.06;
  TArrow a0_16O(St_16O,y0_16O,St_16O,y0_16O+0.05/2,0.01,"<|");
  a0_16O.Draw();
  t_16O.DrawLatex(St_16O,y0_16O+0.06/2,Form("#scale[%f]{gnd (1/2^{-})}",0.75*scale));
    
  Double_t y1_16O=0.3;
  TArrow a1_16O(St_16O+E1_16O,y1_16O,St_16O+E1_16O,y1_16O+0.05/2,0.01,"<|");
  a1_16O.Draw();
  t_16O.DrawLatex(St_16O+E1_16O-0.35,y1_16O+0.06/2,Form("#scale[%f]{2.36 MeV}",0.75*scale));
  t_16O.DrawLatex(St_16O+E1_16O+0.35,y1_16O+0.06/2,Form("#scale[%f]{(1/2^{+})}",0.75*scale));

  Double_t E2_16O=3.502;
  Double_t y2_16O=0.18;
  TArrow a2_16O(St_16O+E2_16O,y2_16O,St_16O+E2_16O,y2_16O+0.05/2,0.01,"<|");
  TArrow a2_16O_1(St_16O+E2_16O,y2_16O+0.05/2,St_16O+E2_16O+1.0,y2_16O+0.1/2,0.01,"");
  a2_16O.Draw();
  a2_16O_1.Draw();  
  t_16O.DrawLatex(St_16O+E2_16O+1.0-0.35,y2_16O+0.11/2,Form("#scale[%f]{3.50 MeV (3/2^{-})}",0.75*scale));
  t_16O.DrawLatex(St_16O+E2_16O+1.0+0.35,y2_16O+0.11/2,Form("#scale[%f]{and 3.54 MeV (5/2^{+})}",0.75*scale));
  
  
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  //  title.DrawLatex(.65,.8,Form("#scale[%f]{Mylar/^{12}C(#it{p,pt})}",1.0*scale));
  title.DrawLatex(.65,.8,Form("#scale[%f]{^{16}O(#it{p,pt})}",1.0*scale));
  title.DrawLatex(.65,.7,Form("#scale[%f]{^{40-48}O(#it{p,pt}) setup}",1.0*scale));  
  //title.DrawLatex(.65,.725,Form("#scale[%f]{#it{S_{t}}=24.996 MeV}",0.8*scale));


  

}
