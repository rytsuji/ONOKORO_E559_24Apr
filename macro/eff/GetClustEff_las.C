{
  gRoot->ProcessLine("sus");

  std::cout <<  "Entry: " << tree->GetEntries() << std::endl;
  TCut x1="@vdc_las_clust_x1.GetEntriesFast()==1";
  TCut x2="@vdc_las_clust_x2.GetEntriesFast()==1";
  TCut u1="@vdc_las_clust_u1.GetEntriesFast()==1";
  TCut u2="@vdc_las_clust_u2.GetEntriesFast()==1";
  TCut v1="@vdc_las_clust_v1.GetEntriesFast()==1";
  TCut v2="@vdc_las_clust_v2.GetEntriesFast()==1";
      
    
  int uv_hit=tree->GetEntries(u1 && u2 && v1 && v2);
  int x1_hit=tree->GetEntries(u1 && u2 && v1 && v2 && x1);
  int x2_hit=tree->GetEntries(u1 && u2 && v1 && v2 && x2);
  std::cout <<  "UV Hit Entry: " << uv_hit << std::endl;
  
  int xv_hit=tree->GetEntries(x1 && x2 && v1 && v2);
  int u1_hit=tree->GetEntries(x1 && x2 && v1 && v2 && u1);
  int u2_hit=tree->GetEntries(x1 && x2 && v1 && v2 && u2);
  std::cout <<  "XV Hit Entry: " << xv_hit << std::endl;

  int xu_hit=tree->GetEntries(u1 && u2 && x1 && x2);
  int v1_hit=tree->GetEntries(u1 && u2 && x1 && x2 && v1);
  int v2_hit=tree->GetEntries(u1 && u2 && x1 && x2 && v2);
  std::cout <<  "XU Hit Entry: " << xu_hit << std::endl;


  std::cout << "---LAS VDC cluster efficiency---" << std::endl;
  std::cout << "X1 : " << (double) x1_hit/uv_hit*100  << "%" << std::endl;
  std::cout << "X2 : " << (double) x2_hit/uv_hit*100  << "%" << std::endl;
  std::cout << "U1 : " << (double) u1_hit/xv_hit*100  << "%" << std::endl;
  std::cout << "U2 : " << (double) u2_hit/xv_hit*100  << "%" << std::endl;
  std::cout << "V1 : " << (double) v1_hit/xu_hit*100  << "%" << std::endl;
  std::cout << "V2 : " << (double) v1_hit/xu_hit*100  << "%" << std::endl;

  std::cout << "---for copy and paste---" << std::endl;
  std::cout <<  (double) x1_hit/uv_hit*100 << " " <<  (double) x2_hit/uv_hit*100 << " " <<  (double) u1_hit/xv_hit*100 << " " <<  (double) u2_hit/xv_hit*100 << " " <<  (double) v1_hit/xu_hit*100 << " " <<  (double) v2_hit/xu_hit*100 << " " << std::endl;
}
