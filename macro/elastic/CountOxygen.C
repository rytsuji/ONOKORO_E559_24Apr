{

  std::vector<double> prm;
  TString input="macro/elastic/prm_contamination/oxygen.dat";
  std::ifstream infile((std::string) input);
  std::string iline;
  while(getline(infile,iline)){    
    std::istringstream iss(iline);
    prm.push_back(std::stod(iline));
  }


  TCut cut="abs(pla_gr_vme_1.fCharge-600)<300";
  //tree->SetAlias("ang","vdc_gr_m.fA*1000");	
  //tree->SetAlias("oxygen","vdc_gr_m.fX-(-93.7606-0.333641*ang-0.00234214*pow(ang,2.0)-3.66596e-06*pow(ang,3.0))");

  
  tree->SetAlias("fci",
                 Form("%e+(%e)*pow(vdc_gr_m.fA*1000,1.0)+(%e)*pow(vdc_gr_m.fA*1000,2.0)+(%e)*pow(vdc_gr_m.fA*1000,3.0)+(%e)*pow(vdc_gr_m.fA*1000,4.0)+(%e)*pow(vdc_gr_m.fA*1000,5.0)",prm[0],prm[1],prm[2],prm[3],prm[4],prm[5]));
  
  tree->Draw("vdc_gr_m.fX-fci>>h(150,-50,100)","abs(vdc_gr_m.fA*1000)<40" && cut,"")

}
