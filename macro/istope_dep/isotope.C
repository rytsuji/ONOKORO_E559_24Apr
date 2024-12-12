void isotope(void){
  //gStyle->SetTitleAlign(22);
  
  std::vector<double> A_ppt;
  std::vector<double> A_ppt_err;  
  std::vector<double> tdx_ppt_exp;
  std::vector<double> tdx_ppt_exp_err;
  std::vector<double> tdx_ppt_exp_err_stat;
  std::vector<double> tdx_ppt_dwia;
  std::vector<double> nt_exp;
  std::vector<double> nt_exp_err;

  std::vector<double> A_pph;
  std::vector<double> A_pph_err;
  std::vector<double> tdx_pph_exp;
  std::vector<double> tdx_pph_exp_err;
  std::vector<double> tdx_pph_exp_err_stat;
  std::vector<double> tdx_pph_dwia;
  std::vector<double> nh_exp;
  std::vector<double> nh_exp_err;

  std::vector<double> A_ppt_th;
  std::vector<double> nt_th;

  std::vector<double> A_pph_th;
  std::vector<double> nh_th;  

  //double err_syt_ppt[4]={0.019,0.017,0.017,0.019};
  //double err_syt_pph[4]={0.016,0.017,0.017,0.018};

  
  std::ifstream InFile_ppt("macro/istope_dep/ppt.dat");
  std::string InLine_ppt;
  while(getline(InFile_ppt,InLine_ppt)){
    std::string Str;
    std::vector<double> Val;
    stringstream SS(InLine_ppt);
    while(getline(SS, Str, ' ')){
      Val.push_back(std::stod(Str));
    }
    A_ppt.push_back(Val[0]);
    A_ppt_err.push_back(0.0);
    tdx_ppt_exp.push_back(Val[1]);
    tdx_ppt_exp_err.push_back(sqrt(pow(Val[3],2.0)+pow(Val[1]*0.1,2.0)+pow(Val[1]*Val[4],2.0)+pow(Val[1]*Val[5],2.0)));
    tdx_ppt_exp_err_stat.push_back(sqrt(pow(Val[3],2.0)+pow(Val[1]*Val[4],2.0)+pow(Val[1]*Val[5],2.0)));
    tdx_ppt_dwia.push_back(Val[2]);
    nt_exp.push_back(Val[1]/Val[2]);        
    nt_exp_err.push_back(sqrt(pow(Val[3],2.0)+pow(Val[1]*0.1,2.0)+pow(Val[1]*Val[4],2.0)+pow(Val[1]*Val[5],2.0))/Val[2]);
  }
  
  std::ifstream InFile_pph("macro/istope_dep/pph.dat");
  std::string InLine_pph;
  while(getline(InFile_pph,InLine_pph)){
    std::string Str;
    std::vector<double> Val;
    stringstream SS(InLine_pph);
    while(getline(SS, Str, ' ')){
      Val.push_back(std::stod(Str));
    }
    
    A_pph.push_back(Val[0]);
    A_pph_err.push_back(0.0);
    tdx_pph_exp.push_back(Val[1]);
    tdx_pph_exp_err.push_back(sqrt(pow(Val[3],2.0)+pow(Val[1]*0.1,2.0)+pow(Val[1]*Val[4],2.0)+pow(Val[1]*Val[5],2.0)));
    tdx_pph_exp_err_stat.push_back(sqrt(pow(Val[3],2.0)+pow(Val[1]*Val[4],2.0)+pow(Val[1]*Val[5],2.0)));
    tdx_pph_dwia.push_back(Val[2]);
    nh_exp.push_back(Val[1]/Val[2]);        
    nh_exp_err.push_back(sqrt(pow(Val[3],2.0)+pow(Val[1]*0.1,2.0)+pow(Val[1]*Val[4],2.0)+pow(Val[1]*Val[5],2.0))/Val[2]);
  }
  
  std::ifstream InFile_ppt_th("macro/istope_dep/theory/out_Ca_np3H_v1.dat");
  std::string InLine_ppt_th;
  while(getline(InFile_ppt_th,InLine_ppt_th)){
    std::string Str;
    std::vector<double> Val;
    stringstream SS(InLine_ppt_th);
    while(getline(SS, Str, ' ')){
      Val.push_back(std::stod(Str));
    }    
    A_ppt_th.push_back(Val[0]);
    nt_th.push_back(Val[5]);
  }

  std::ifstream InFile_pph_th("macro/istope_dep/theory/out_Ca_np3He_v1.dat");
  std::string InLine_pph_th;
  while(getline(InFile_pph_th,InLine_pph_th)){
    std::string Str;
    std::vector<double> Val;
    stringstream SS(InLine_pph_th);
    while(getline(SS, Str, ' ')){
      Val.push_back(std::stod(Str));
    }    
    A_pph_th.push_back(Val[0]);
    nh_th.push_back(Val[5]);
  }
  
 
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
  xtitle.DrawLatex(0.5,0.5*(bmargin),"#scale[0.6]{mass number #it{A}}");

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
  /************* Pad0 *************/
  pad0->cd();
  TMultiGraph *mg0 = new TMultiGraph();
  mg0->SetTitle("TDX experiment");
  TAxis *axis0 = mg0->GetXaxis();  
  axis0->SetLimits(38.,50.);            
  mg0->GetHistogram()->SetMaximum(0.29999); 
  mg0->GetHistogram()->SetMinimum(0.0001);
  
  auto gr0_ppt = new TGraphErrors(A_ppt.size(),&A_ppt[0],&tdx_ppt_exp[0],&A_ppt_err[0],&tdx_ppt_exp_err[0]);
  gr0_ppt->SetMarkerColor(2);
  gr0_ppt->SetMarkerSize(2.0);  
  gr0_ppt->SetMarkerStyle(20);
  gr0_ppt->SetLineStyle(1);  
  
  auto gr0_pph = new TGraphErrors(A_pph.size(),&A_pph[0],&tdx_pph_exp[0],&A_pph_err[0],&tdx_pph_exp_err[0]);
  gr0_pph->SetMarkerColor(4);
  gr0_pph->SetMarkerSize(2.0);    
  gr0_pph->SetMarkerStyle(22);
  gr0_pph->SetLineStyle(9);  
  
  mg0->Add(gr0_ppt);
  mg0->Add(gr0_pph);
  mg0->Draw("ALP");

  TLegend *legend0= new TLegend(0.7,0.7,0.8,0.9);
  legend0->AddEntry(gr0_ppt,"(#it{p,pt})","lp");
  legend0->AddEntry(gr0_pph,"(#it{p,p}^{3}He)","lp");  
  legend0->Draw("same");
  legend0->SetBorderSize(0);
  
  TLatex ytitle0;
  ytitle0.SetTextAlign(22);
  ytitle0.SetNDC(1);
  ytitle0.SetTextAngle(90);
  ytitle0.DrawLatex(0.05,0.5,"#scale[0.8]{#it{d#sigma/dE_{p}d#Omega_{p}d#Omega_{X}} (#it{#mu}b#upoint MeV^{-1}#upoint str^{-2})}");

  /************* Pad1 *************/
  pad1->cd();
  TMultiGraph *mg1 = new TMultiGraph();
  mg1->SetTitle("TDX DWIA");
  TAxis *axis1 = mg1->GetXaxis();
  axis1->SetLimits(38.,50.);                 
  mg1->GetHistogram()->SetMaximum(1.9999);   
  mg1->GetHistogram()->SetMinimum(0.0001);
    
  auto gr1_ppt = new TGraphErrors(A_ppt.size(),&A_ppt[0],&tdx_ppt_dwia[0],&A_ppt_err[0],&A_ppt_err[0]);  
  gr1_ppt->SetMarkerColor(2);
  gr1_ppt->SetMarkerSize(2.0);  
  gr1_ppt->SetMarkerStyle(20);
  gr1_ppt->SetLineStyle(1);  
  auto gr1_pph = new TGraphErrors(A_pph.size(),&A_pph[0],&tdx_pph_dwia[0],&A_pph_err[0],&A_pph_err[0]);
  gr1_pph->SetMarkerColor(4);
  gr1_pph->SetMarkerSize(2.0);    
  gr1_pph->SetMarkerStyle(22);
  gr1_pph->SetLineStyle(9);  

  mg1->Add(gr1_ppt);
  mg1->Add(gr1_pph);
  mg1->Draw("ALP");

  TLegend *legend1= new TLegend(0.7,0.2,0.8,0.4);
  legend1->AddEntry(gr1_ppt,"(#it{p,pt})","lp");
  legend1->AddEntry(gr1_pph,"(#it{p,p}^{3}He)","lp");  
  legend1->Draw("same");
  legend1->SetBorderSize(0);

  TLatex ytitle1;
  ytitle1.SetTextAlign(22);
  ytitle1.SetNDC(1);
  ytitle1.SetTextAngle(90);
  ytitle1.DrawLatex(0.05,0.5,"#scale[0.8]{#it{d#sigma/dE_{p}d#Omega_{p}d#Omega_{X}} (#it{#mu}b#upoint MeV^{-1}#upoint str^{-2})}");

  /************* Pad2 *************/
  pad2->cd();
  TMultiGraph *mg2 = new TMultiGraph();
  mg2->SetTitle("number of clusters");
  TAxis *axis2 = mg2->GetXaxis();
  axis2->SetLimits(38.,50.);
  mg2->GetHistogram()->SetMaximum(0.19999);
  mg2->GetHistogram()->SetMinimum(0.0001);
  
  auto gr2_ppt = new TGraphErrors(A_ppt.size(),&A_ppt[0],&nt_exp[0],&A_ppt_err[0],&nt_exp_err[0]);  
  gr2_ppt->SetMarkerColor(2);
  gr2_ppt->SetMarkerSize(2.0);  
  gr2_ppt->SetMarkerStyle(20);
  gr2_ppt->SetLineStyle(1);
  
  auto gr2_pph = new TGraphErrors(A_pph.size(),&A_pph[0],&nh_exp[0],&A_pph_err[0],&nh_exp_err[0]);
  gr2_pph->SetMarkerColor(4);
  gr2_pph->SetMarkerSize(2.0);    
  gr2_pph->SetMarkerStyle(22);
  gr2_pph->SetLineStyle(9);  

  auto gr2_ppt_th = new TGraph(A_ppt_th.size(),&A_ppt_th[0],&nt_th[0]);
  gr2_ppt_th->SetMarkerColor(800);
  gr2_ppt_th->SetMarkerSize(2.0);  
  gr2_ppt_th->SetMarkerStyle(24);
  gr2_ppt_th->SetLineStyle(2);
  
  auto gr2_pph_th = new TGraph(A_pph_th.size(),&A_pph_th[0],&nh_th[0]);
  gr2_pph_th->SetMarkerColor(3);
  gr2_pph_th->SetMarkerSize(2.0);  
  gr2_pph_th->SetMarkerStyle(26);
  gr2_pph_th->SetLineStyle(10);
  mg2->Add(gr2_ppt);
  mg2->Add(gr2_pph);
  mg2->Add(gr2_ppt_th);
  mg2->Add(gr2_pph_th);
  mg2->Draw("ALP");
  
  TLegend *legend2= new TLegend(0.7,0.5,0.8,0.9);
  legend2->AddEntry(gr2_ppt,"#it{t} experiment","lp");
  legend2->AddEntry(gr2_pph,"^{3}He experiment","lp");
  legend2->AddEntry(gr2_ppt_th,"#it{t} thepry","lp");
  legend2->AddEntry(gr2_pph_th,"^{3}He theory","lp");    
  legend2->SetBorderSize(0);
  legend2->Draw("");

  TLatex ytitle2;
  ytitle2.SetTextAlign(22);
  ytitle2.SetNDC(1);
  ytitle2.SetTextAngle(90);
  ytitle2.DrawLatex(0.05,0.5,"#scale[0.8]{#it{n_{X}} (#it{X}=#it{t}, ^{3}He)}");
  
  /************* Pad3 *************/
  pad3->cd();
  Double_t ratio[3];
  Double_t ratio_err[3];
  ratio[0]=nh_exp[0]/nt_exp[0];
  ratio[1]=nh_exp[1]/nt_exp[2];
  ratio[2]=nh_exp[2]/nt_exp[3];
  ratio_err[0]=nh_exp[0]/nt_exp[0]*sqrt(pow(tdx_ppt_exp_err_stat[0]/tdx_ppt_exp[0],2.0)+pow(tdx_pph_exp_err_stat[0]/tdx_pph_exp[0],2.0));
  ratio_err[1]=nh_exp[1]/nt_exp[2]*sqrt(pow(tdx_ppt_exp_err_stat[2]/tdx_ppt_exp[2],2.0)+pow(tdx_pph_exp_err_stat[1]/tdx_pph_exp[1],2.0));
  ratio_err[2]=nh_exp[2]/nt_exp[3]*sqrt(pow(tdx_ppt_exp_err_stat[3]/tdx_ppt_exp[3],2.0)+pow(tdx_pph_exp_err_stat[2]/tdx_pph_exp[2],2.0));

  std::vector<Double_t> ratio_th;
  for(int i=0; i<A_pph_th.size();i++){
    ratio_th.push_back(nh_th[i]/nt_th[i]);
  }

  TMultiGraph *mg3 = new TMultiGraph();
  mg3->SetTitle("ratio of clusters");
  TAxis *axis3 = mg3->GetXaxis();
  axis3->SetLimits(38.,50.);
  mg3->GetHistogram()->SetMaximum(4.999);
  mg3->GetHistogram()->SetMinimum(0.0001);
 
  auto gr3= new TGraphErrors(A_pph.size(),&A_pph[0],ratio,&A_pph_err[0],ratio_err);  
  gr3->SetMarkerColor(2);
  gr3->SetMarkerSize(2.0);  
  gr3->SetMarkerStyle(21);
  gr3->SetLineStyle(1);
  
  auto gr3_th= new TGraph(A_pph_th.size(),&A_pph_th[0],&ratio_th[0]);
  gr3_th->SetMarkerColor(4);
  gr3_th->SetMarkerSize(2.0);  
  gr3_th->SetMarkerStyle(25);
  gr3_th->SetLineStyle(9);
  
  mg3->Add(gr3);
  mg3->Add(gr3_th);
  mg3->Draw("ALP");

  TLegend *legend3= new TLegend(0.7,0.7,0.8,0.9);
  legend3->AddEntry(gr3,"experiment","lp");
  legend3->AddEntry(gr3_th,"theory","lp");  
  legend3->Draw("same");
  legend3->SetBorderSize(0);

  TLatex ytitle3;
  ytitle3.SetTextAlign(22);
  ytitle3.SetNDC(1);
  ytitle3.SetTextAngle(90);
  ytitle3.DrawLatex(0.05,0.5,"#scale[0.8]{#it{n}_{^{3}He}/#it{n_{t}}}");

  TLine *line = new TLine(38,1.46,50,1.46);
  line->SetLineStyle(2);
  line->Draw();
  TLatex txt12C;
  txt12C.SetTextAlign(22);
  txt12C.SetNDC(1);
  txt12C.SetTextAngle(0);
  txt12C.DrawLatex(0.8,0.4,"#scale[0.8]{^{12}C #it{#sigma}_{(#it{p},#it{p}^{3}He)} / #it{#sigma}_{(#it{p},#it{pt})}}");
  /*************************** Save ***************************/
  c1->SaveAs("figs/sx_fit/isotope.pdf");
  c1->SaveAs("figs/sx_fit/isotope.png");
}
