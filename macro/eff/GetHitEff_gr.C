{
  int clust_size=3;

  gROOT->ProcessLine("sus");  
  
    
  TCut x1=Form("@vdc_gr_x1.GetEntriesFast()>%d",clust_size-1);
  TCut x2=Form("@vdc_gr_x2.GetEntriesFast()>%d",clust_size-1);
  TCut u1=Form("@vdc_gr_u1.GetEntriesFast()>%d",clust_size-1);
  TCut u2=Form("@vdc_gr_u2.GetEntriesFast()>%d",clust_size-1);

      
  int all_hit=tree->GetEntries(x1 && x2 &&u1 && u2);
  int x2u1u2_hit=tree->GetEntries(u1 && u2 && x2);
  int x1u1u2_hit=tree->GetEntries(u1 && u2 && x1);
  int x1x2u2_hit=tree->GetEntries(x1 && x2 && u2);
  int x1x2u1_hit=tree->GetEntries(x1 && x2 && u1);


  
  std::cout << "---GR VDC hit efficiency---" << std::endl;
  std::cout << "X1 : " << (double) all_hit/x2u1u2_hit*100  << "%" << std::endl;
  std::cout << "X2 : " << (double) all_hit/x1u1u2_hit*100  << "%" << std::endl;
  std::cout << "U1 : " << (double) all_hit/x1x2u2_hit*100  << "%" << std::endl;
  std::cout << "U2 : " << (double) all_hit/x1x2u1_hit*100  << "%" << std::endl;



}
