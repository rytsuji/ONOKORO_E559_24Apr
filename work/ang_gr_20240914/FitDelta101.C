{
  TFile *_file0 = TFile::Open("output/gr/run1035.root");  
  TF1 *g1=new TF1("g1","gaus(0)",-200,200);    
  TF1 *g3=new TF1("g3","gaus(0)+gaus(3)+gaus(6)",-200,200);  
  TF1 *g5=new TF1("g5","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)",-200,200);

  //X Fit
  TH1F *hx=new TH1F("hx","hx",1000,-1000,1000);
  tree->Draw("gfp.fX>>hx","","");
  hx->Fit("g1","","",225,237);
  double x=g1->GetParameter(1);
  TCut xcut=Form("Entry$<60000 && abs(gfp.fX-(%e))<10",x);
  //A Fit
  TH1F *ha=new TH1F("ha","ha",1000,-0.1,0.1);
  tree->Draw("gfp.fA>>ha",xcut,"");

  double const_a[5]={100.0,100.0,100.0,100.0,100.0};
  double mean_a[5]={-0.023,-0.005,0.015,0.035,0.055};
  double sigma_a[5]={2.5e-03,2.5e-03,2.5e-03,2.5e-03,2.5e-03};

  for(int i=0; i<5; i++){
    g5->SetParameter(3*i,const_a[i]);
    g5->SetParameter(3*i+1,mean_a[i]);    
    g5->SetParameter(3*i+2,sigma_a[i]);    
  }
  ha->Fit("g5");
  
  TCut acut[5];    
  for(int i=0;i<5;i++){
    double mean=g5->GetParameter(3*i+1);
    double sigma=g5->GetParameter(3*i+2);    
    mean_a[i]=mean;
    acut[i]=Form("abs(gfp.fA-(%e))<%e",mean,fabs(sigma));

  }

  double min_y[5]={-30,-40,-30,-25,0};
  double max_y[5]={30,35,30,25,0};  

  double const_y[5][5]={{0,300,300,300,0},
			{300,500,500,500,300},
			{1000,1000,1300,1000,800},
			{1000,2000,3500,2000,1000},
			{0,0,0,0,0}};  

  double mean_y[5][5]={{0,-21,-3.5,12,0},
		       {-33.5,-18,-2,14,30},
		       {-28,-15,-2,11,23.7},
		       {-18.4,-10.75,-1.35,7.7,15.3},
		       {0,0,0,0,0}};

  double sigma_y=3.0;


  TH1F *hy[5];
  TH1F *ha_ycut[5][5];  
  TH1F *hb[5][5];
  double y[5][5];
  double a[5][5];
  double b[5][5];
  

  
  for(int i=0;i<5;i++){
    hy[i]=new TH1F(Form("hy[%d]",i),Form("hy[%d]",i),200,-100,100);
    TString draw=Form("gfp.fY>>hy[%d]",i);
    tree->Draw(draw,acut[i],"");
  }

  for(int i=0;i<5;i++){
    if(i==0){
      for(int j=0; j<3; j++){
	g3->SetParameter(3*j,const_y[i][j+1]);
	g3->SetParameter(3*j+1,mean_y[i][j+1]);
	g3->SetParameter(3*j+2,sigma_y);
      }
      
      hy[i]->Fit("g3","","",min_y[i],max_y[i]);      
      for(int j=0; j<3; j++){
	TCut ycut=Form("abs(gfp.fY-%e)<%e",g3->GetParameter(3*j+1),g3->GetParameter(3*j+2));
	ha_ycut[i][j+1]=new TH1F(Form("ha_ycut[%d][%d]",i,j+1),Form("ha_ycut[%d][%d]",i,j+1),500,-0.1,0.1);
	TString draw_a=Form("gdc.fA>>ha_ycut[%d][%d]",i,j+1);
	tree->Draw(draw_a,ycut && xcut,"");
	ha_ycut[i][j+1]->Fit("g1","","",mean_a[i]-0.01,mean_a[i]+0.01);
	y[i][j+1]=g3->GetParameter(3*j+1);
	a[i][j+1]=g1->GetParameter(1);	

        TString draw_b=Form("gfp.fB>>hb[%d][%d]",i,j+1);
	hb[i][j+1]=new TH1F(Form("hb[%d][%d]",i,j+1),Form("hb[%d][%d]",i,j+1),500,-0.05,0.06);
	tree->Draw(draw_b,ycut && xcut && acut[i],"");
	hb[i][j+1]->Fit("g1");
	b[i][j+1]=g1->GetParameter(1);	
      }
      


    }else if(i==4){
      TH1F * hb4=new TH1F("hb4","hb4",250,-0.1,0.1);
      TH1F * hy4_bcut[3];
      TH1F * ha4_bcut[3];
      tree->Draw("gfp.fB>>hb4",xcut && acut[i],"");
      g3->SetParameters(100,-0.0046,0.0015,100,-0.001,0.0015,100,0.002,0.0015);
      hb4->Fit("g3","","",-0.007,0.004);
      b[4][1]=g3->GetParameter(7);
      b[4][2]=g3->GetParameter(4);
      b[4][3]=g3->GetParameter(1);
      for(int j=0;j<3;j++){
        TCut bcut=Form("abs(gfp.fB-%e)<%e",b[4][j+1],g3->GetParameter(8-3*j));
        ha4_bcut[j]=new TH1F(Form("ha4_bcut[%d]",j),Form("ha4_bcut[%d]",j),500,-0.1,0.1);
        hy4_bcut[j]=new TH1F(Form("hy4_bcut[%d]",j),Form("hy4_bcut[%d]",j),500,-100,100);
        TString drawa=Form("gdc.fA>>ha4_bcut[%d]",j);
        TString drawy=Form("gdc.fY>>hy4_bcut[%d]",j);
        tree->Draw(drawa,xcut && bcut,"");
        ha4_bcut[j]->Fit("g1","","",mean_a[4]-0.01,mean_a[4]+0.01);
        a[4][j+1]=g1->GetParameter(1);

        tree->Draw(drawy,xcut && bcut && acut[4],"");
        hy4_bcut[j]->Fit("g1","","");
        y[4][j+1]=g1->GetParameter(1);
      }

    }else{    
      for(int j=0; j<5; j++){
	g5->SetParameter(3*j,const_y[i][j]);
	g5->SetParameter(3*j+1,mean_y[i][j]);
	g5->SetParameter(3*j+2,sigma_y);
      }
      hy[i]->Fit("g5","","",min_y[i],max_y[i]);
      for(int j=0; j<5; j++){
	TCut ycut=Form("abs(gfp.fY-%e)<%e",g5->GetParameter(3*j+1),g5->GetParameter(3*j+2));
	ha_ycut[i][j]=new TH1F(Form("ha_ycut[%d][%d]",i,j),Form("ha_ycut[%d][%d]",i,j),500,-0.1,0.1);
	TString draw=Form("gdc.fA>>ha_ycut[%d][%d]",i,j);
	tree->Draw(draw,ycut && xcut,"");
	ha_ycut[i][j]->Fit("g1","","",mean_a[i]-0.01,mean_a[i]+0.01);
	y[i][j]=g5->GetParameter(3*j+1);
	a[i][j]=g1->GetParameter(1);

	TString draw_b=Form("gfp.fB>>hb[%d][%d]",i,j);
        hb[i][j]=new TH1F(Form("hb[%d][%d]",i,j),Form("hb[%d][%d]",i,j),500,-0.05,0.06);
        tree->Draw(draw_b,ycut && xcut && acut[i],"");
        hb[i][j]->Fit("g1");
        b[i][j]=g1->GetParameter(1);
      }      
    }
  }

  TH2F *h_ay=new TH2F("h_ay","h_ay",1000,-0.1,0.1,1000,-150,150);
  TH2F *h_ay_fit=new TH2F("h_ay_fit","h_ay_fit",1000,-0.1,0.1,1000,-150,150);
  TH2F *h_yb_fit=new TH2F("h_yb_fit","h_yb_fit",1000,-150,150,1000,-0.1,0.1);
  tree->Draw("gfp.fY:gfp.fA>>h_ay",xcut,"");
  

  ofstream ofile("work/ang_gr/dat/delta101.dat");
  
  for(int i=0;i<5;i++){
    if(i==0 || i==4){
      for(int j=0; j<3; j++){
        ofile  << x << " " << a[i][j+1] << " " << y[i][j+1] << " " << b[i][j+1] << " " << (2-i)*5.0/577.5 << " "<< (j+1-2)*12.0/577.5  <<std::endl;
	h_ay_fit->Fill(a[i][j+1],y[i][j+1]);
	h_yb_fit->Fill(y[i][j+1],b[i][j+1]);
      }
    }else if(i==3){
      for(int j=1; j<4; j++){
	ofile << x << " " << a[i][j] << " " << y[i][j] << " " << b[i][j] << " " << (2-i)*5.0/577.5 << " "<< (j-2)*12.0/577.5  <<std::endl;
	h_ay_fit->Fill(a[i][j],y[i][j]);
	h_yb_fit->Fill(y[i][j],b[i][j]);
      }      
    }else{
      for(int j=0; j<5; j++){
	ofile << x << " " << a[i][j] << " " << y[i][j] << " " << b[i][j] << " " << (2-i)*5.0/577.5 << " "<< (j-2)*12.0/577.5  <<std::endl;
	h_ay_fit->Fill(a[i][j],y[i][j]);
	h_yb_fit->Fill(y[i][j],b[i][j]);
      }
    }
    
  }

  ofile.close();

}
