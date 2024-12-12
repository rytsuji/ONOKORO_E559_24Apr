void pph_48Ca(void){
  TCut agr="abs(pgr.GetTheta()-50.5)<0.8 && abs(pgr.GetPhi())<3.5 && abs(pgr.GetPhi())<(4.0*pgr.GetTheta()-197.3) && abs(pgr.GetPhi())<(-5.0*pgr.GetTheta()+260)";
  TCut alas="abs(plas.GetTheta()-49)<3 && abs(fmod(plas.GetPhi()+360.0,360.0)-180)<3.5";
  TCut egr="pgr.fTKE>136 && pgr.fTKE<146";
  TCut elas="plas.fTKE>44 && plas.fTKE<69";

  TCut tc="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))>-20 && (tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))<20";
  TCut ac="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>-320 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<-20) || (tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>20 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<320)";

  Int_t xBin=200;
  Double_t xMin=0.0;
  Double_t xMax=50.0;
  
  TH1F *htc=new TH1F("htc","htc",xBin,xMin,xMax);
  TH1F *hac=new TH1F("hac","hac",xBin,xMin,xMax);
  TH1F *htcg=new TH1F("htcg","htcg",xBin,xMin,xMax);
  TH1F *hacg=new TH1F("hacg","hacg",xBin,xMin,xMax);  
  double BeamE=225.98;
  double scale_ac=-1.0/8.0;

  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>htc",BeamE),elas && egr && tc,"");
  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>hac",BeamE),elas && egr && ac,"");

  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>htcg",BeamE),alas && agr && elas && egr && tc,"");
  tree->Draw(Form("%f-pgr.fTKE-plas.fTKE>>hacg",BeamE),alas && agr && elas && egr && ac,"");

  htc->Sumw2();
  hac->Sumw2();
  htcg->Sumw2();
  hacg->Sumw2();

  TH1F *sx = (TH1F*) htc->Clone("sx");
  TH1F *sxg = (TH1F*) htcg->Clone("sxg");
  //sx->Sumw2(); not requreid?
  //sxg->Sumw2(); not requreid?

  sx->Add(hac,scale_ac);
  sxg->Add(hacg,scale_ac);


  TH1F *sx0 = (TH1F*) sx->Clone("sx0");
  TH1F *sxg0 = (TH1F*) sxg->Clone("sxg0");
  sx0->Sumw2(0);
  sxg0->Sumw2(0);

  TH1F *sx_scale = (TH1F*) sx->Clone();
  sx_scale->SetName("sx_scale");
  sx_scale->Scale(0.33353696);
  sx_scale->SetLineColor(2);
  sx_scale->SetMarkerColor(2);


  TH1F *sx_scale0 = (TH1F*) sx_scale->Clone();
  sx_scale0->SetName("sx_scale0");
  sx_scale0->Sumw2(0);  
  sx_scale0->SetLineColor(2);
  sx_scale0->SetMarkerColor(2);

  //sxg->Rebin(2);
  //sxg0->Rebin(2);
  //sx_scale->Rebin(2);
  //sx_scale0->Rebin(2);
  gApplication->ProcessLine("zon");  
  gApplication->ProcessLine("ht sx_scale");  
  gApplication->ProcessLine("ht sx_scale0 same");  
  gApplication->ProcessLine("ht sxg same");
  gApplication->ProcessLine("ht sxg0 same");


}
