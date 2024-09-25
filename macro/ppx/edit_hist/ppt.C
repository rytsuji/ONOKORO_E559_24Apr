{
  double lmargin=0.05;
  double tmargin=0.05;
  double xlabelmargin=0.05;
  double bmargin=0.05+xlabelmargin;
  int NPad=4;

  double dy=(1.0-tmargin-bmargin)/(double) NPad;
  
  //TCanvas *c1 = new TCanvas("c1","c1",800,1600);
  //TCanvas *c1 = new TCanvas("c1","c1",500,1000);

  TCanvas *c1 = new TCanvas("c1","c1",2000,3000);  

  c1->cd();
  TLatex xtitle;
  xtitle.SetTextAlign(22);
  xtitle.SetNDC(1);
  xtitle.SetTextAngle(0);
  xtitle.DrawLatex(0.5,0.75*(bmargin-xlabelmargin),"#scale[0.8]{Separation energy #it{S_{X}} (MeV)}");

  TLatex ytitle;
  ytitle.SetTextAlign(22);
  ytitle.SetNDC(1);
  ytitle.SetTextAngle(90);
  ytitle.DrawLatex(lmargin*0.6,0.5,"#scale[0.8]{#it{d#sigma/dE_{p}d#Omega_{p}d#Omega_{X}dS_{X}} (#it{#mu}b/MeV#upoint str^{2}  per 200 keV)}");
  
  //TPad *pad0 = new TPad("pad0", "pad0",0.0,1.0-0.25*1,1.00,1.00);


  TPad *pad0 = new TPad("pad0", "pad0",
			lmargin,bmargin+dy*(double)(NPad-1),
			1.00,1.00-tmargin);
  pad0->SetTopMargin(0.0);
  pad0->SetBottomMargin(0.0);
  pad0->Draw();
  //TPad *pad1 = new TPad("pad1", "pad1",0.0,1.0-0.25*2,1.00,1.00-0.25*1);
  TPad *pad1 = new TPad("pad1", "pad1",
			lmargin,bmargin+dy*(double)(NPad-2),
			1.00,bmargin+dy*(double)(NPad-1));
  
  pad1->SetTopMargin(0.0);
  pad1->SetBottomMargin(0.0);
  pad1->Draw();

  TPad *pad2 = new TPad("pad2", "pad2",
			lmargin,bmargin+dy*(double)(NPad-3),
			1.00,bmargin+dy*(double)(NPad-2));
  pad2->SetTopMargin(0.0);
  pad2->SetBottomMargin(0.0);
  pad2->Draw();
  
  
  TPad *pad3 = new TPad("pad3", "pad3",
			lmargin,bmargin+dy*(double)(NPad-4)-xlabelmargin,
			1.00,bmargin+dy*(double)(NPad-3));
  pad3->SetTopMargin(0.0);
  pad3->SetBottomMargin(0.1);
  pad3->Draw();
  
  pad0->cd();
  gApplication->ProcessLine(".x macro/ppx/edit_hist/ppt_40Ca.C");
  gApplication->ProcessLine(".x macro/ppx/edit_hist/ppt_40Ca.C");

  pad1->cd();
  gApplication->ProcessLine(".x macro/ppx/edit_hist/ppt_42Ca.C");
  gApplication->ProcessLine(".x macro/ppx/edit_hist/ppt_42Ca.C");


  pad2->cd();
  gApplication->ProcessLine(".x macro/ppx/edit_hist/ppt_44Ca.C");
  gApplication->ProcessLine(".x macro/ppx/edit_hist/ppt_44Ca.C");

  
  pad3->cd();
  gApplication->ProcessLine(".x macro/ppx/edit_hist/ppt_48Ca.C");
  gApplication->ProcessLine(".x macro/ppx/edit_hist/ppt_48Ca.C");
  




}
