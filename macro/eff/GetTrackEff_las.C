{

  gROOT->ProcessLine("sus");
  
  TCut x1="@vdc_las_clust_x1.GetEntriesFast()==1";
  TCut x2="@vdc_las_clust_x2.GetEntriesFast()==1";
  TCut u1="@vdc_las_clust_u1.GetEntriesFast()==1";
  TCut u2="@vdc_las_clust_u2.GetEntriesFast()==1";
  TCut v1="@vdc_las_clust_v1.GetEntriesFast()==1";
  TCut v2="@vdc_las_clust_v2.GetEntriesFast()==1";

  TCut tr_xu="vdc_las_xu.fX>-650 && vdc_las_xu.fX<550";
  TCut tr_uv="vdc_las_uv.fX>-650 && vdc_las_uv.fX<550";
  TCut tr_xv="vdc_las_xv.fX>-650 && vdc_las_xv.fX<550";
	

  int x1_hit=tree->GetEntries(tr_uv && x1);
  int x2_hit=tree->GetEntries(tr_uv && x2);
  int u1_hit=tree->GetEntries(tr_xv && u1);
  int u2_hit=tree->GetEntries(tr_xv && u2);
  int v1_hit=tree->GetEntries(tr_xu && v1);
  int v2_hit=tree->GetEntries(tr_xu && v2);  


  int xu_track=tree->GetEntries(tr_xu);
  int xv_track=tree->GetEntries(tr_xv);
  int uv_track=tree->GetEntries(tr_uv);
  
  std::cout << "Entry: " << tree->GetEntries() << std::endl;

  
  std::cout << "---LAS VDC cluster efficiency---" << std::endl;
  std::cout << "X1 : " << (double) x1_hit/uv_track*100  << "%" << std::endl;
  std::cout << "X2 : " << (double) x2_hit/uv_track*100  << "%" << std::endl;
  std::cout << "U1 : " << (double) u1_hit/xv_track*100  << "%" << std::endl;
  std::cout << "U2 : " << (double) u2_hit/xv_track*100  << "%" << std::endl;
  std::cout << "V1 : " << (double) v1_hit/xu_track*100  << "%" << std::endl;
  std::cout << "V2 : " << (double) v2_hit/xu_track*100  << "%" << std::endl;

  Double_t eff_xu=(double) x1_hit/uv_track*x2_hit/uv_track*u1_hit/xv_track*u2_hit/xv_track;
  Double_t eff_xv=(double) x1_hit/uv_track*x2_hit/uv_track*v1_hit/xu_track*v1_hit/xu_track;
  Double_t eff_uv=(double) u1_hit/xv_track*u2_hit/xv_track*v1_hit/xu_track*v1_hit/xu_track;

  std::cout << "---LAS VDC tracking efficiency---" << std::endl;
  std::cout << "X-U : " << eff_xu*100.0  << "%" << std::endl;
  std::cout << "X-V : " << eff_xv*100.0  << "%" << std::endl;
  std::cout << "U-V : " << eff_uv*100.0  << "%" << std::endl;
  std::cout << "Merge : " << (eff_xu + (1-eff_xu)*eff_xv + (1-eff_xu)*(1-eff_xv)*eff_uv)*100.0  << "%" << std::endl;


  


}
