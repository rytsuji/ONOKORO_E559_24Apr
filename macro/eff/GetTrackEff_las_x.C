{

  gROOT->ProcessLine("sus");
  //tree->SetAlias("RF1","fmod(pid_las.fTiming-rf1.fTiming+1420.6750,71.033750)");
  //tree->SetAlias("RF2","fmod(pid_las.fTiming-rf2.fTiming+1420.6750,71.033750)");
  //tree->SetAlias("RF3","fmod(pid_las.fTiming-rf3.fTiming+1420.6750,71.033750)");
  //TCut pid=" pid_las.fCharge > 100 && pid_las.fCharge < 4000  && RF3 > 10 && RF3 < 55 ";//ppt
  TCut pid="1";
  
  
  TCut x1="@vdc_las_clust_x1.GetEntriesFast()==1";
  TCut x2="@vdc_las_clust_x2.GetEntriesFast()==1";
  TCut u1="@vdc_las_clust_u1.GetEntriesFast()==1";
  TCut u2="@vdc_las_clust_u2.GetEntriesFast()==1";
  TCut v1="@vdc_las_clust_v1.GetEntriesFast()==1";
  TCut v2="@vdc_las_clust_v2.GetEntriesFast()==1";

  const int n_x=12;
  TCut tr_xu[n_x];
  TCut tr_xv[n_x];
  TCut tr_uv[n_x];

  Double_t eff[6][n_x];
  Double_t eff_xu[n_x];
  Double_t eff_xv[n_x];
  Double_t eff_uv[n_x];
  const double dx=1200.0/(double) n_x;



  
  for(int i=0;i<n_x;i++){
    tr_xu[i]=Form("vdc_las_xu.fX>%e && vdc_las_xu.fX<%e",(double) i*dx -650.0,(double) (i+1)*dx -650.0);
    tr_xv[i]=Form("vdc_las_xv.fX>%e && vdc_las_xv.fX<%e",(double) i*dx -650.0,(double) (i+1)*dx -650.0);
    tr_uv[i]=Form("vdc_las_uv.fX>%e && vdc_las_uv.fX<%e",(double) i*dx -650.0,(double) (i+1)*dx -650.0);
  }

  std::cout << "---LAS X1 Hit  efficiency---" << std::endl;
  for(int i=0;i<n_x;i++){    
    eff[0][i]=(double) tree->GetEntries(pid && x1 && tr_uv[i])/tree->GetEntries(pid && tr_uv[i]);
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff[0][i]*100.0 << "%" << std::endl;
  }

  std::cout << "---LAS X2 Hit  efficiency---" << std::endl;
  for(int i=0;i<n_x;i++){    
    eff[1][i]=(double) tree->GetEntries(pid && x2 && tr_uv[i])/tree->GetEntries(pid && tr_uv[i]);
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff[1][i]*100.0 << "%" << std::endl;
  }

  std::cout << "---LAS U1 Hit  efficiency---" << std::endl;
  for(int i=0;i<n_x;i++){    
    eff[2][i]=(double) tree->GetEntries(pid && u1 && tr_xv[i])/tree->GetEntries(pid &&tr_xv[i]);
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff[2][i]*100.0 << "%" << std::endl;
  }

  std::cout << "---LAS U2 Hit  efficiency---" << std::endl;
  for(int i=0;i<n_x;i++){    
    eff[3][i]=(double) tree->GetEntries(pid && u2 && tr_xv[i])/tree->GetEntries(pid && tr_xv[i]);
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff[3][i]*100.0 << "%" << std::endl;
  }

  std::cout << "---LAS V1 Hit  efficiency---" << std::endl;
  for(int i=0;i<n_x;i++){    
     eff[4][i]=(double) tree->GetEntries(pid && v1 && tr_xu[i])/tree->GetEntries(pid && tr_xu[i]);
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff[4][i]*100.0 << "%" << std::endl;
  }

  std::cout << "---LAS V2 Hit  efficiency---" << std::endl;
  for(int i=0;i<n_x;i++){    
    eff[5][i]=(double) tree->GetEntries(pid && v2 && tr_xu[i])/tree->GetEntries(pid && tr_xu[i]);
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff[5][i]*100.0 << "%" << std::endl;
  }


  std::cout << "************LAS XU Tracking efficiency ************" << std::endl;
  for(int i=0;i<n_x;i++){    
    eff_xu[i]=eff[0][i]*eff[1][i]*eff[2][i]*eff[3][i];
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff_xu[i]*100.0 << "%" << std::endl;
  }

    std::cout << "************LAS XV Tracking efficiency ************" << std::endl;
  for(int i=0;i<n_x;i++){    
    eff_xv[i]=eff[0][i]*eff[1][i]*eff[4][i]*eff[5][i];
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff_xv[i]*100.0 << "%" << std::endl;
  }

    std::cout << "************LAS XV Tracking efficiency ************" << std::endl;
  for(int i=0;i<n_x;i++){    
    eff_uv[i]=eff[4][i]*eff[5][i]*eff[2][i]*eff[3][i];
    std::cout << "x=" << (double)i*dx -650.0 << " to " << (double) (i+1)*dx -650.0 << "(mm) :  " << eff_uv[i]*100.0 << "%" << std::endl;
  }


  for(int i=0;i<n_x;i++){    
    std::cout << ((double)i+0.5)*dx -650.0 << " " << eff_xu[i]  << " " << eff_xv[i]  << " " << eff_uv[i] << std::endl;
  }

  
  
}
