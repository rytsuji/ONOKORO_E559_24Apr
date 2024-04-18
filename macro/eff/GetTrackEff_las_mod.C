{

  TCut x1="@vdc_las_clust_x1.GetEntriesFast()==1";
  TCut x2="@vdc_las_clust_x2.GetEntriesFast()==1";
  TCut u1="@vdc_las_clust_u1.GetEntriesFast()==1";
  TCut u2="@vdc_las_clust_u2.GetEntriesFast()==1";
  TCut v1="@vdc_las_clust_v1.GetEntriesFast()==1";
  TCut v2="@vdc_las_clust_v2.GetEntriesFast()==1";

  TCut tr_xu="@vdc_las_xu.GetEntriesFast()>0";
  TCut tr_uv="@vdc_las_uv.GetEntriesFast()>0";
  TCut tr_xv="@vdc_las_xv.GetEntriesFast()>0";

  TCut x_xu="abs(vdc_las_xu.fX+100)<500";
  TCut x_xv="abs(vdc_las_xv.fX+100)<500";
  TCut x_uv="abs(vdc_las_uv.fX+100)<500";

  //int uv_hit=tree->GetEntries(u1 && u2 && v1 && v2);
  //int x1_hit=tree->GetEntries(u1 && u2 && v1 && v2 && x1);
  //int x2_hit=tree->GetEntries(u1 && u2 && v1 && v2 && x2);
  int u1_hit=tree->GetEntries(tr_xv  && u1 && x_xv);
  int u2_hit=tree->GetEntries(tr_xv  && u2 && x_xv);
  
  //int xv_hit=tree->GetEntries(x1 && x2 && v1 && v2);
  //int u1_hit=tree->GetEntries(x1 && x2 && v1 && v2 && u1);
  //int u2_hit=tree->GetEntries(x1 && x2 && v1 && v2 && u2);
  int x1_hit=tree->GetEntries(tr_uv  && x1 && x_uv);
  int x2_hit=tree->GetEntries(tr_uv  && x2 && x_uv);
  
  //int xu_hit=tree->GetEntries(u1 && u2 && x1 && x2);
  //int v1_hit=tree->GetEntries(u1 && u2 && x1 && x2 && v1);
  //int v2_hit=tree->GetEntries(u1 && u2 && x1 && x2 && v2);
  int v1_hit=tree->GetEntries(tr_xu  && v1 && x_xu);
  int v2_hit=tree->GetEntries(tr_xu  && v2 && x_xu);

  int xu=tree->GetEntries(tr_xu && x_xu);
  int uv=tree->GetEntries(tr_uv && x_uv);
  int xv=tree->GetEntries(tr_xv && x_xv);
  
  //int v_hit=tree->GetEntries(v1 && v2);
  //int xu_track=tree->GetEntries(v1 && v2 && tr_xu);

  //int x_hit=tree->GetEntries(x1 && x2);
  //int uv_track=tree->GetEntries(x1 && x2 && tr_uv);
  
  //int u_hit=tree->GetEntries(u1 && u2);
  //int xv_track=tree->GetEntries(u1 && u2 && tr_xv);

  /*
  std::cout << "---LAS VDC cluster efficiency---" << std::endl;
  std::cout << "X1 : " << (double) x1_hit/uv_hit*100  << "%" << std::endl;
  std::cout << "X2 : " << (double) x2_hit/uv_hit*100  << "%" << std::endl;
  std::cout << "U1 : " << (double) u1_hit/xv_hit*100  << "%" << std::endl;
  std::cout << "U2 : " << (double) u2_hit/xv_hit*100  << "%" << std::endl;
  std::cout << "V1 : " << (double) v1_hit/xu_hit*100  << "%" << std::endl;
  std::cout << "V2 : " << (double) v1_hit/xu_hit*100  << "%" << std::endl;
  */
  
  std::cout << "---LAS VDC cluster efficiency---" << std::endl;
  std::cout << "X1 : " << (double) x1_hit/uv*100  << "%" << std::endl;
  std::cout << "X2 : " << (double) x2_hit/uv*100  << "%" << std::endl;
  std::cout << "U1 : " << (double) u1_hit/xv*100  << "%" << std::endl;
  std::cout << "U2 : " << (double) u2_hit/xv*100  << "%" << std::endl;
  std::cout << "V1 : " << (double) v1_hit/xu*100  << "%" << std::endl;
  std::cout << "V2 : " << (double) v2_hit/xu*100  << "%" << std::endl;
  
  /*
  std::cout << "---LAS VDC tracking efficiency---" << std::endl;
  std::cout << "X-U : " << (double) xu_track/v_hit*100  << "%" << std::endl;
  std::cout << "U-V : " << (double) uv_track/x_hit*100  << "%" << std::endl;
  std::cout << "V-X : " << (double) xv_track/u_hit*100  << "%" << std::endl;
  */
  double eff_xu=((double)x1_hit/uv)*((double)x2_hit/uv)*((double)u1_hit/xv)*((double)u2_hit/xv);
  double eff_uv=((double)v1_hit/xu)*((double)v2_hit/xu)*((double)u1_hit/xv)*((double)u2_hit/xv);
  double eff_xv=((double)x1_hit/uv)*((double)x2_hit/uv)*((double)v1_hit/xu)*((double)v2_hit/xu);

  std::cout << "---LAS VDC tracking efficiency---" << std::endl;
  std::cout << "X-U : " << (double) eff_xu*100  << "%" << std::endl;
  std::cout << "U-V : " << (double) eff_uv*100  << "%" << std::endl;
  std::cout << "V-X : " << (double) eff_xv*100  << "%" << std::endl;

  std::cout << "Total : " << (double) (eff_xu+(1-eff_xu)*(eff_xv+(1-eff_xv)*eff_uv))*100  << "%" << std::endl;
				       


}
