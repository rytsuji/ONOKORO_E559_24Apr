{
  double scale=1.0;
  TFile *file_40Ca = TFile::Open("output/calib_pid/hist_ex/ppt_40Ca_40Ca.root");
  //TH1F *sx=(TH1F*)file_40Ca->Get("sx")->Clone("sx");
  //TH1F *sx0=(TH1F*)file_40Ca->Get("sx0")->Clone("sx0");

  Double_t ymin = -0.051;
  Double_t ymax = 0.155;

  sx->SetLineColor(2);
  sx0->SetLineColor(2);
  sx->SetMarkerColor(2);
  sx0->SetMarkerColor(2);


  sx->Rebin(10);
  sx0->Rebin(10);



  sx->SetTitle("");
  sx->GetXaxis()->SetTitle("#mbox{E_{X}} (MeV)");
  //sx->GetYaxis()->SetTitle("#mbox{d#sigma/dT_{p}d#Omega_{p}d#Omega_{X}} (#mbox{#mu}b/MeV#upoint str^{2}  per 200 keV)");                                        
  sx->SetLabelSize(0.045,"xy");
  sx->SetTitleSize(0.045,"xy");
  sx->GetXaxis()->CenterTitle(true);
  sx->GetYaxis()->CenterTitle(true);
  sx->SetStats(0);

  double scale_16O=(0.21808865/(11.8/39.962))*0.0943;
  int Nbin=sx->GetXaxis()->GetNbins();
  double dx=sx->GetXaxis()->GetXmax()-sx->GetXaxis()->GetXmin();

  double St=24.996;
  TF1 *f_16O_ppt = new TF1("f_16O_ppt",
                       "([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",
		       -1000,1000);
  f_16O_ppt->SetParameters(0.1*((double) dx/Nbin)*scale_16O,2.48938e+01-St,
		       0.355*((double) dx/Nbin)*scale_16O,2.84556e+01-St,
		       3.10261e-01);

  sx->Add(f_16O_ppt,-1.0);
  sx0->Add(f_16O_ppt,-1.0);  

  sx->GetXaxis()->SetRange(sx->FindBin(-1),sx->FindBin(15));
  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);
  
  sx->Draw();
  sx0->Draw("same");


  
  TFile *file_40Ca_pph = TFile::Open("output/calib_pid/hist_ex/pph_40Ca_40Ca.root");
  sx->Rebin(10);
  sx0->Rebin(10);

  double Sh=18.830;
  TF1 *f_16O_pph= new TF1("f_16O_pph",
			  "([0]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[1])/[4],2))+([2]/sqrt(2.*TMath::Pi()*[4]*[4]))*exp(-0.5*pow((x-[3])/[4],2))",
			  -1000,1000);
  f_16O_pph->SetParameters(0.191*((double) dx/Nbin)*scale_16O,2.28804e+01-Sh,
			   0.503*((double) dx/Nbin)*scale_16O,2.62719e+01-Sh,
			   3.10261e-01);

  sx->Add(f_16O_pph,-1.0);
  sx0->Add(f_16O_pph,-1.0);  




  sx->Scale(1.0/1.64);
  sx0->Scale(1.0/1.64);
  sx0->Sumw2(0);

  sx->Draw("same E1");
  sx0->Draw("same");

  Double_t Et[5]={0.0, 
		  1370.85/1000.0, //1/2+
		  2285.24/1000.0, //5/2+, 7/2+
		  2750.22/1000.0, //5/2+
		  3239.5/1000.0,  //5/2+
  };

  Double_t yt[5]={0.05,0.11,0.04,0.05,0.04};

  TLatex text_t;
  text_t.SetTextAlign(12);
  text_t.SetTextAngle(90);
  text_t.SetTextColor(2);

  int nt=0;
  TArrow at0(Et[nt],yt[nt],Et[nt],yt[nt]+0.02,0.01,"<|");
  at0.SetLineColor(2);
  at0.SetFillColor(2);  
  at0.Draw();
  text_t.DrawLatex(Et[nt],yt[nt]+0.025,Form("#scale[%f]{3/2^{+} (gs)}",0.75));

  nt=1;
  TArrow at1(Et[nt],yt[nt],Et[nt],yt[nt]+0.02,0.01,"<|");
  at1.SetLineColor(2);
  at1.SetFillColor(2);  
  at1.Draw();
  text_t.DrawLatex(Et[nt],yt[nt]+0.025,Form("#scale[%f]{1/2^{+}}",0.75));

  nt=2;
  TArrow at2(Et[nt],yt[nt],Et[nt],yt[nt]+0.02,0.01,"<|");
  at2.SetLineColor(2);
  at2.SetFillColor(2);  
  at2.Draw();
  text_t.DrawLatex(Et[nt],yt[nt]+0.025,Form("#scale[%f]{5/2^{+},7/2^{+}}",0.75));

  nt=3;
  TArrow at3(Et[nt],yt[nt],Et[nt],yt[nt]+0.03,0.01,"<|");
  at3.SetLineColor(2);
  at3.SetFillColor(2);  
  at3.Draw();
  TArrow at3_1(Et[nt],yt[nt]+0.03,Et[nt]+0.25,yt[nt]+0.06,0.01,"");
  at3_1.SetLineColor(2);
  at3_1.SetFillColor(2);  
  at3_1.Draw();
  text_t.DrawLatex(Et[nt]+0.25,yt[nt]+0.065,Form("#scale[%f]{5/2^{+}}",0.75));

  nt=4;
  TArrow at4(Et[nt],yt[nt],Et[nt],yt[nt]+0.02,0.01,"<|");
  at4.SetLineColor(2);
  at4.SetFillColor(2);  
  at4.Draw();
  text_t.DrawLatex(Et[nt],yt[nt]+0.025,Form("#scale[%f]{5/2^{+}}",0.75));

  
  Double_t Eh[5]={0.0, 
		  1409.84/1000.0, //1/2+
		  2217.00/1000.0, //7/2+
		  2796.15/1000.0, //5/2+
		  3170.0/1000.0,  //5/2+
  };


  TLatex text_h;
  text_h.SetTextAlign(12);
  text_h.SetTextAngle(90);
  text_h.SetTextColor(602);
  
  int nh=0;
  TArrow ah0(Eh[nh],-0.02,Eh[nh],0.0,0.01,"|>");
  ah0.SetLineColor(602);
  ah0.SetFillColor(602);  
  ah0.Draw();
  text_h.DrawLatex(Eh[nh],-0.045,Form("#scale[%f]{3/2^{+}}",0.75));
  text_h.DrawLatex(Eh[nh]+0.5,-0.045,Form("#scale[%f]{(gs)}",0.75));

  nh=1;
  TArrow ah1(Eh[nh],-0.02,Eh[nh],0.0,0.01,"|>");
  ah1.SetLineColor(602);
  ah1.SetFillColor(602);  
  ah1.Draw();
  text_h.DrawLatex(Eh[nh],-0.045,Form("#scale[%f]{1/2^{+}}",0.75));

  nh=2;
  TArrow ah2(Eh[nh],-0.02,Eh[nh],0.0,0.01,"|>");
  ah2.SetLineColor(602);
  ah2.SetFillColor(602);  
  ah2.Draw();
  text_h.DrawLatex(Eh[nh],-0.045,Form("#scale[%f]{7/2^{+}}",0.75));

  nh=3;
  TArrow ah3(Eh[nh],-0.02,Eh[nh],0.0,0.01,"|>");
  ah3.SetLineColor(602);
  ah3.SetFillColor(602);  
  ah3.Draw();
  text_h.DrawLatex(Eh[nh],-0.045,Form("#scale[%f]{5/2^{+}}",0.75));

  nh=4;
  TArrow ah4(Eh[nh],-0.02,Eh[nh],0.0,0.01,"|>");
  ah4.SetLineColor(602);
  ah4.SetFillColor(602);  
  ah4.Draw();
  text_h.DrawLatex(Eh[nh],-0.045,Form("#scale[%f]{5/2^{+}}",0.75));

  
}
