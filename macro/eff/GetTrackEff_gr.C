{
  gROOT->ProcessLine("sus");
 
  TCut x1="@vdc_gr_clust_x1.GetEntriesFast()==1";
  TCut x2="@vdc_gr_clust_x2.GetEntriesFast()==1";
  TCut u1="@vdc_gr_clust_u1.GetEntriesFast()==1";
  TCut u2="@vdc_gr_clust_u2.GetEntriesFast()==1";

      
  int all_hit=tree->GetEntries(x1 && x2 && u1 && u2);    
  int x2u1u2_hit=tree->GetEntries(x2 && u1 && u2);
  int x1u1u2_hit=tree->GetEntries(x1 && u1 && u2);
  int x1x2u2_hit=tree->GetEntries(x1 && x2 && u2);
  int x1x2u1_hit=tree->GetEntries(x1 && x2 && u1);

  double eff_x1=(double) all_hit/x2u1u2_hit;
  double eff_x2=(double) all_hit/x1u1u2_hit;
  double eff_u1=(double) all_hit/x1x2u2_hit;
  double eff_u2=(double) all_hit/x1x2u1_hit;
  
  std::cout << "---GR VDC cluster efficiency---" << std::endl;
  std::cout << "X1 : " << eff_x1*100  << "%" << std::endl;
  std::cout << "X2 : " << eff_x2*100  << "%" << std::endl;
  std::cout << "U1 : " << eff_u1*100  << "%" << std::endl;
  std::cout << "U2 : " << eff_u2*100  << "%" << std::endl;
  
  std::cout << "---GR VDC  tracking efficiency---" << std::endl;

  std::cout <<  eff_x1*eff_x2*eff_u1*eff_u2*100.0  << "%" << std::endl;
  
}
