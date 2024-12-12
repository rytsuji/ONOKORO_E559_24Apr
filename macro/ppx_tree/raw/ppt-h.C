{
  double BeamE=225.98;
  double scale_ac=-1.0/8.0;

  TCut agr="abs(pgr.GetTheta()-51.2)<1.0 && abs(pgr.GetPhi())<3.5 && abs(pgr.GetPhi())<(4.0*pgr.GetTheta()-199.3) && abs(pgr.GetPhi())<(-5.0*pgr.GetTheta()+262.5)";
  TCut alas="abs(plas.GetTheta()-51)<3 && abs(fmod(plas.GetPhi()+360.0,360.0)-180)<3.5";
  TCut egr="pgr.fTKE>145 && pgr.fTKE<155";
  TCut elas="plas.fTKE>44 && plas.fTKE<69";
  TCut tc="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))>-35 && (tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))<35";
  TCut ac="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>-320 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<-35) || (tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>35 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<320)";

  TCut tp_gate1=Form("abs(%f-pgr.fTKE-plas.fTKE-20.8)<0.3",BeamE);
  TCut tp_gate2=Form("abs(%f-pgr.fTKE-plas.fTKE-22.1)<0.5",BeamE);
  //TCut tp_gate=Form("abs(%f-pgr.fTKE-plas.fTKE-26.1)<0.5",BeamE);
  
  TH1F *htc=new TH1F("htc","htc",200,0,50);
  TH1F *hac=new TH1F("hac","hac",200,0,50);  
  TH1F *htcg=new TH1F("htcg","htcg",200,0,50);
  TH1F *hacg=new TH1F("hacg","hacg",200,0,50);
  TH1F *htc_nogate=new TH1F("htc_nogate","htc_nogate",200,0,50);
  TH1F *hac_nogte=new TH1F("hac_nogate","hac_nogate",200,0,50);

  TH1F *htp_tc1=new TH1F("htp_tc1","htp_tc1",20,140,160);
  TH1F *htp_ac1=new TH1F("htp_ac1","htp_ac1",20,140,160);
  tree->Draw(Form("pgr.fTKE>>htp_tc1"),tc && tp_gate1,"");
  tree->Draw(Form("pgr.fTKE>>htp_ac1"),ac && tp_gate1,"");
  TH1F *htp_tc2=new TH1F("htp_tc2","htp_tc2",20,140,160);
  TH1F *htp_ac2=new TH1F("htp_ac2","htp_ac2",20,140,160);
  tree->Draw(Form("pgr.fTKE>>htp_tc2"),tc && tp_gate2,"");
  tree->Draw(Form("pgr.fTKE>>htp_ac2"),ac && tp_gate2,"");
  TH1F *htp1 = (TH1F*) htp_tc1->Clone("htp1");
  TH1F *htp2 = (TH1F*) htp_tc2->Clone("htp2");
  htp_tc1->Sumw2();
  htp_ac1->Sumw2();
  htp1->Sumw2();
  htp_tc2->Sumw2();
  htp_ac2->Sumw2();
  htp2->Sumw2();
  htp1->Add(htp_ac1,scale_ac);
  htp2->Add(htp_ac2,scale_ac);
  TH1F *htp10 = (TH1F*) htp1->Clone("htp10");  
  htp10->Sumw2(0);
  TH1F *htp20 = (TH1F*) htp2->Clone("htp20");  
  htp20->Sumw2(0);  

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
  TH1F *sx_nogate0 = (TH1F*) sx_nogate->Clone("sx_nogate0");  
  sx0->Sumw2(0);
  sxg0->Sumw2(0);
  sx_nogate0->Sumw2(0);


  
  sx_nogate->SetLineColor(2);
  sx_nogate0->SetLineColor(2);
  sx_nogate->SetMarkerColor(2);
  
  
  sx->SetLineColor(3);
  sx0->SetLineColor(3);
  sx->SetMarkerColor(3);
  
  gApplication->ProcessLine("ht sx_nogate");
  gApplication->ProcessLine("ht sx_nogate0 same");
  gApplication->ProcessLine("ht sx same");
  gApplication->ProcessLine("ht sx0 same");
  gApplication->ProcessLine("ht sxg same");
  gApplication->ProcessLine("ht sxg0 same");


}
