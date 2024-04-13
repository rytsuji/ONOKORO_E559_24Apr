{
  //run4206

  TString oname="macro/elastic/prm_contamination/oxygen.dat";
  ofstream ofile((std::string) oname);

  TCut cut="abs(pla_gr_vme_1.fCharge-600)<300";
  TH2F* h_xa= new TH2F("h_xa","",70,-140,-70,50,-50,50);
  tree->Draw("vdc_gr_m.fA*1000:vdc_gr_m.fX>>h_xa",cut,"colz");
  TF1 *f= new TF1("f","pol5",-1000,1000);
  h_xa->FitSlicesX();
  h_xa_1->Fit("f","","",-48,48);

  const int n_prm=6;
  
  double prm[n_prm];
  for(int i=0;i<n_prm;i++){
    prm[i]=f->GetParameter(i);
  }
  

  tree->SetAlias("fc",
		 Form("%e+(%e)*pow(vdc_gr_m.fA*1000,1.0)+(%e)*pow(vdc_gr_m.fA*1000,2.0)+(%e)*pow(vdc_gr_m.fA*1000,3.0)+(%e)*pow(vdc_gr_m.fA*1000,4.0)+(%e)*pow(vdc_gr_m.fA*1000,5.0)",prm[0],prm[1],prm[2],prm[3],prm[4],prm[5]));
  
  TCut locus="abs(vdc_gr_m.fX-fc)<20";  
  TH2F* h_ax_cut= new TH2F("h_ax_cut","",120,-60,60,70,-140,-70);
  tree->Draw("vdc_gr_m.fX:vdc_gr_m.fA*1000>>h_ax_cut",locus,"colz");
  h_ax_cut->Fit("f","","",-50,50);

  for(int i=0;i<n_prm;i++){
    prm[i]=f->GetParameter(i);
    ofile << prm[i] << std:: endl; 
  }
  
  tree->SetAlias("fci",
		 Form("%e+(%e)*pow(vdc_gr_m.fA*1000,1.0)+(%e)*pow(vdc_gr_m.fA*1000,2.0)+(%e)*pow(vdc_gr_m.fA*1000,3.0)+(%e)*pow(vdc_gr_m.fA*1000,4.0)+(%e)*pow(vdc_gr_m.fA*1000,5.0)",prm[0],prm[1],prm[2],prm[3],prm[4],prm[5]));

  tree->Draw("vdc_gr_m.fX-fci>>h(100,-50,50)",cut && "abs(vdc_gr_m.fA*1000)>10","");
  
  ofile.close();
}
