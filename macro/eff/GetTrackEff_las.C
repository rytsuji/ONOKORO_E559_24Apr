{

  gROOT->ProcessLine("sus");
  
  TCut x1="@vdc_las_clust_x1.GetEntriesFast()==1";
  TCut x2="@vdc_las_clust_x2.GetEntriesFast()==1";
  TCut u1="@vdc_las_clust_u1.GetEntriesFast()==1";
  TCut u2="@vdc_las_clust_u2.GetEntriesFast()==1";
  TCut v1="@vdc_las_clust_v1.GetEntriesFast()==1";
  TCut v2="@vdc_las_clust_v2.GetEntriesFast()==1";

  TCut tr_xu="@vdc_las_xu.GetEntriesFast()==1";
  TCut tr_uv="@vdc_las_uv.GetEntriesFast()==1";
  TCut tr_xv="@vdc_las_xv.GetEntriesFast()==1";
	

  int uv_hit=tree->GetEntries(u1 && u2 && v1 && v2);
  int x1_hit=tree->GetEntries(u1 && u2 && v1 && v2 && x1);
  int x2_hit=tree->GetEntries(u1 && u2 && v1 && v2 && x2);

  int xv_hit=tree->GetEntries(x1 && x2 && v1 && v2);
  int u1_hit=tree->GetEntries(x1 && x2 && v1 && v2 && u1);
  int u2_hit=tree->GetEntries(x1 && x2 && v1 && v2 && u2);

  int xu_hit=tree->GetEntries(u1 && u2 && x1 && x2);
  int v1_hit=tree->GetEntries(u1 && u2 && x1 && x2 && v1);
  int v2_hit=tree->GetEntries(u1 && u2 && x1 && x2 && v2);


  
  int v_hit=tree->GetEntries(v1 && v2);
  int xu_track=tree->GetEntries(v1 && v2 && tr_xu);

  int u_hit=tree->GetEntries(u1 && u2);
  int xv_track=tree->GetEntries(u1 && u2 && tr_xv);

  int x_hit=tree->GetEntries(x1 && x2);
  int uv_track=tree->GetEntries(x1 && x2 && tr_uv);
  


  std::cout << "---LAS VDC cluster efficiency---" << std::endl;
  std::cout << "X1 : " << (double) x1_hit/uv_hit*100  << "%" << std::endl;
  std::cout << "X2 : " << (double) x2_hit/uv_hit*100  << "%" << std::endl;
  std::cout << "U1 : " << (double) u1_hit/xv_hit*100  << "%" << std::endl;
  std::cout << "U2 : " << (double) u2_hit/xv_hit*100  << "%" << std::endl;
  std::cout << "V1 : " << (double) v1_hit/xu_hit*100  << "%" << std::endl;
  std::cout << "V2 : " << (double) v1_hit/xu_hit*100  << "%" << std::endl;

  Double_t eff_xu=(double) xu_track/v_hit;
  Double_t eff_xv=(double) xv_track/u_hit;
  Double_t eff_uv=(double) uv_track/x_hit;

  std::cout << "---LAS VDC tracking efficiency---" << std::endl;
  std::cout << "X-U : " << eff_xu*100.0  << "%" << std::endl;
  std::cout << "X-V : " << eff_xv*100.0  << "%" << std::endl;
  std::cout << "U-V : " << eff_uv*100.0  << "%" << std::endl;
  std::cout << "Merge : " << (eff_xu + (1-eff_xu)*eff_xv + (1-eff_xu)*(1-eff_xv)*eff_uv)*100.0  << "%" << std::endl;


  


}
