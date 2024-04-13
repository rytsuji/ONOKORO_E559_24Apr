{
  int clust_size=3;

  
  gROOT->ProcessLine("sus");
    
  TCut x1=Form("@vdc_las_x1.GetEntriesFast()>%d",clust_size-1);
  TCut x2=Form("@vdc_las_x2.GetEntriesFast()>%d",clust_size-1);
  TCut u1=Form("@vdc_las_u1.GetEntriesFast()>%d",clust_size-1);
  TCut u2=Form("@vdc_las_u2.GetEntriesFast()>%d",clust_size-1);
  TCut v1=Form("@vdc_las_v1.GetEntriesFast()>%d",clust_size-1);
  TCut v2=Form("@vdc_las_v2.GetEntriesFast()>%d",clust_size-1);
      
  int uv_hit=tree->GetEntries(u1 && u2 && v1 && v2);
  int x1_hit=tree->GetEntries(u1 && u2 && v1 && v2 && x1);
  int x2_hit=tree->GetEntries(u1 && u2 && v1 && v2 && x2);

  int xv_hit=tree->GetEntries(x1 && x2 && v1 && v2);
  int u1_hit=tree->GetEntries(x1 && x2 && v1 && v2 && u1);
  int u2_hit=tree->GetEntries(x1 && x2 && v1 && v2 && u2);

  int xu_hit=tree->GetEntries(u1 && u2 && x1 && x2);
  int v1_hit=tree->GetEntries(u1 && u2 && x1 && x2 && v1);
  int v2_hit=tree->GetEntries(u1 && u2 && x1 && x2 && v2);

  
  std::cout << "---LAS VDC hit efficiency---" << std::endl;
  std::cout << "X1 : " << (double) x1_hit/uv_hit*100  << "%" << std::endl;
  std::cout << "X2 : " << (double) x2_hit/uv_hit*100  << "%" << std::endl;
  std::cout << "U1 : " << (double) u1_hit/xv_hit*100  << "%" << std::endl;
  std::cout << "U2 : " << (double) u2_hit/xv_hit*100  << "%" << std::endl;
  std::cout << "V1 : " << (double) v1_hit/xu_hit*100  << "%" << std::endl;
  std::cout << "V2 : " << (double) v1_hit/xu_hit*100  << "%" << std::endl;


}
