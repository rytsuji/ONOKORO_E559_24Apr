{
  TCut agr="abs(pgr.GetTheta()-51.2)<1.0 && abs(pgr.GetPhi())<3.5 && abs(pgr.GetPhi())<(4.0*pgr.GetTheta()-199.3) && abs(pgr.GetPhi())<(-5.0*pgr.GetTheta()+262.5)";
  TCut alas="abs(plas.GetTheta()-50.9)<3.4 && abs(fmod(plas.GetPhi()+360.0,360.0)-180)<3.5";
  TCut egr="pgr.fTKE>143 && pgr.fTKE<156";
  TCut elas="plas.fTKE>44 && plas.fTKE<68";
  TCut tc="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))>-20 && (tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))<20";
  TCut ac="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>-320 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<-20) || (tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>20 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<320)";

  TH1F *htc=new TH1F("htc","htc",200,0,50);
  TH1F *hac=new TH1F("hac","hac",200,0,50);  
  TH1F *htcg=new TH1F("htcg","htcg",200,0,50);
  TH1F *hacg=new TH1F("hacg","hacg",200,0,50);
  TH1F *htc_nogate=new TH1F("htc_nogate","htc_nogate",200,0,50);
  TH1F *hac_nogte=new TH1F("hac_nogate","hac_nogate",200,0,50);

  double BeamE=225.98;
  double scale_ac=-1.0/8.0;

  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>htc",BeamE),elas && egr && tc,"");
  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>hac",BeamE),elas && egr && ac,"");
  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>htcg",BeamE),alas && agr && elas && egr && tc,"");
  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>hacg",BeamE),alas && agr && elas && egr && ac,"");
  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>htc_nogate",BeamE),tc,"");
  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>hac_nogate",BeamE),ac,"");

  TH1F *sx = (TH1F*) htc->Clone("sx");
  TH1F *sxg = (TH1F*) htcg->Clone("sxg");   
  TH1F *sx_nogate = (TH1F*) htc_nogate->Clone("sx_nogate");

  htc->Sumw2();  
  hac->Sumw2();
  sx->Sumw2();
  htcg->Sumw2();
  hacg->Sumw2();
  sxg->Sumw2();
  htc_nogate->Sumw2();  
  hac_nogate->Sumw2();
  sx_nogate->Sumw2();
  
  sx->Add(hac,scale_ac);
  sxg->Add(hacg,scale_ac);
  sx_nogate->Add(hac_nogate,scale_ac);

  TH1F *sx0 = (TH1F*) sx->Clone("sx0");
  TH1F *sxg0 = (TH1F*) sxg->Clone("sxg0");
  sx0->Sumw2(0);
  sxg0->Sumw2(0);

  TH1F *sx_scale = (TH1F*) sx->Clone("sx_scale");
  sx_scale->Sumw2();
  sx_scale->Scale(0.51112347);
  sx_scale->SetLineColor(2);
  sx_scale->SetMarkerColor(2);

  TH1F *sx_scale0 = (TH1F*) sx_scale->Clone("sx_scale0");
  sx_scale0->Sumw2(0);
  sx_scale0->SetLineColor(2);
  sx_scale0->SetMarkerColor(2);

  //sxg->Rebin(2);
  //sxg0->Rebin(2);
  //sx_scale->Rebin(2);
  //sx_scale0->Rebin(2);
  
  gApplication->ProcessLine("ht sxg");
  gApplication->ProcessLine("ht sxg0 same");
  gApplication->ProcessLine("ht sx_scale same");  
  gApplication->ProcessLine("ht sx_scale0 same");

}
