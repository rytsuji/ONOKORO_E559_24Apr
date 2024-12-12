{
  double lmargin=0.1;
  double xlabelmargin=0.1;
  double tmargin=0.025;
  double bmargin=0.05;
  int NPad=4;

  double dy=(1.0-tmargin-bmargin)/((double) NPad + xlabelmargin);

  
  //TCanvas *c1 = new TCanvas("c1","c1",800,1600);
  //TCanvas *c1 = new TCanvas("c1","c1",500,1000);


  TCanvas *c1 = new TCanvas("c1","c1",1500,3000*0.2+540*NPad);
  c1->cd();
  TLatex xtitle;
  xtitle.SetTextAlign(22);
  xtitle.SetNDC(1);
  xtitle.SetTextAngle(0);
  xtitle.DrawLatex(0.5,0.5*(bmargin),"#scale[0.8]{Separation energy #it{S_{X}} (MeV)}");

  TLatex ytitle;
  ytitle.SetTextAlign(22);
  ytitle.SetNDC(1);
  ytitle.SetTextAngle(90);
  ytitle.DrawLatex(lmargin*0.6,0.5,"#scale[0.8]{#it{d#sigma/dE_{p}d#Omega_{p}d#Omega_{X}dS_{X}} (#it{#mu}b#upoint MeV^{-1}#upoint str^{-2}/200 keV)}");
  
  //TPad *pad0 = new TPad("pad0", "pad0",0.0,1.0-0.25*1,1.00,1.00);


  TPad *pad0 = new TPad("pad0", "pad0",
			lmargin,1.00-tmargin-dy*1.0,
			1.00,1.00-tmargin);
  pad0->SetTopMargin(0.0);
  pad0->SetBottomMargin(0.0);
  pad0->Draw();

  TPad *pad1 = new TPad("pad1", "pad1",
			lmargin,1.00-tmargin-dy*2.0,
			1.00,1.00-tmargin-dy*1.0);
  
  pad1->SetTopMargin(0.0);
  pad1->SetBottomMargin(0.0);
  pad1->Draw();

  TPad *pad2 = new TPad("pad2", "pad2",
			lmargin,1.00-tmargin-dy*3.0,
			1.00,1.00-tmargin-dy*2.0);
  pad2->SetTopMargin(0.0);
  pad2->SetBottomMargin(0.0);
  pad2->Draw();
  
  TPad *pad3 = new TPad("pad3", "pad3",
			lmargin,1.00-tmargin-dy*4.0-dy*0.1, 
			1.00,1.00-tmargin-dy*3.0);						

  pad3->SetTopMargin(0.0);
  pad3->SetBottomMargin(xlabelmargin);
  pad3->Draw();
  
  pad0->cd();
  gApplication->ProcessLine(".x macro/ppx/edit_hist/pph_40Ca.C");
  gApplication->ProcessLine(".x macro/ppx/edit_hist/pph_40Ca.C");

  pad1->cd();
  gApplication->ProcessLine(".x macro/ppx/edit_hist/pph_42Ca.C");
  gApplication->ProcessLine(".x macro/ppx/edit_hist/pph_42Ca.C");


  pad2->cd();
  gApplication->ProcessLine(".x macro/ppx/edit_hist/pph_44Ca.C");
  gApplication->ProcessLine(".x macro/ppx/edit_hist/pph_44Ca.C");

  
  pad3->cd();
  gApplication->ProcessLine(".x macro/ppx/edit_hist/pph_48Ca.last.C");
  gApplication->ProcessLine(".x macro/ppx/edit_hist/pph_48Ca.last.C");  
  c1->SaveAs("figs/sx_fit/pph.pdf");
  c1->SaveAs("figs/sx_fit/pph.png");



}
