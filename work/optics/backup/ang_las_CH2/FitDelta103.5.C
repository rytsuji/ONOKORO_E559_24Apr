{
  TFile *_file0 = TFile::Open("output/las/run1046.root");  
  TF1 *g1=new TF1("g1","gaus(0)",-200,200);      

  TCut xacut=Form("abs(lfp.fA+1.842808e-01/1000.*lfp.fX+0.055)<0.03");
  
  //A Y cut
  Double_t arange[6]={-0.12,-0.085,-0.045,-0.002,0.05,0.05};
  Double_t yrange[5][6]={{-40,-40,-10,15,50,50},
			 {-60,-60,-20,25,60,60},
			 {-90,-90,-20,30,90,90},
			 {-120,-150,-40,35,150,120},
			 {0,0,0,0,0,0}};			 			 			 
  
  TCut acut[5];
  TCut ycut[5][5];
  for(int i=0;i<5;i++){
    acut[i]=Form("lfp.fA>%e && lfp.fA<%e",arange[i],arange[i+1]);
    for(int j=0;j<5;j++){
      ycut[i][j]=Form("lfp.fY>%e && lfp.fY<%e",yrange[i][j],yrange[i][j+1]);    
    }
  }
  TH1F *hx[5][5];    
  TH1F *ha[5][5];
  TH1F *hy[5][5];
  TH1F *hb[5][5];
  
  //Draw
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      hx[i][j]=new TH1F(Form("hx[%d][%d]",i,j),Form("hx[%d][%d]",i,j),200,-1000,1000);      
      ha[i][j]=new TH1F(Form("ha[%d][%d]",i,j),Form("ha[%d][%d]",i,j),200,-0.3,0.3);
      hy[i][j]=new TH1F(Form("hy[%d][%d]",i,j),Form("hy[%d][%d]",i,j),200,-250,250);
      hb[i][j]=new TH1F(Form("hb[%d][%d]",i,j),Form("hb[%d][%d]",i,j),200,-0.2,0.2);
      TString drawx=Form("lfp.fX>>hx[%d][%d]",i,j);
      TString drawa=Form("lfp.fA>>ha[%d][%d]",i,j);
      TString drawy=Form("lfp.fY>>hy[%d][%d]",i,j);
      TString drawb=Form("lfp.fB>>hb[%d][%d]",i,j);
      tree->Draw(drawx,xacut && acut[i] && ycut[i][j],"");      
      tree->Draw(drawa,xacut && acut[i] && ycut[i][j],"");
      tree->Draw(drawy,xacut && acut[i] && ycut[i][j],"");
      tree->Draw(drawb,xacut && acut[i] && ycut[i][j],"");

    }
  }
  
  
  
  //Fit
  ofstream ofile("work/ang_las_CH2/dat/delta103.5.dat");

  Double_t xfp[5][5];
  Double_t afp[5][5];
  Double_t yfp[5][5];
  Double_t bfp[5][5];

  Double_t atgt[5][5];
  Double_t btgt[5][5];
  
  for(int i=0;i<4;i++){
    //if(i==0){
    for(int j=1;j<4;j++){
	double xc=hx[i][j]->GetXaxis()->GetBinCenter(hx[i][j]->GetMaximumBin());
	hx[i][j]->Fit("g1","","",xc-40.0,xc+40.0);
	xfp[i][j]=g1->GetParameter(1);
	
	double ac=ha[i][j]->GetXaxis()->GetBinCenter(ha[i][j]->GetMaximumBin());
	ha[i][j]->Fit("g1","","",ac-0.04,ac+0.04);
	afp[i][j]=g1->GetParameter(1);

	double yc=hy[i][j]->GetXaxis()->GetBinCenter(hy[i][j]->GetMaximumBin());
	hy[i][j]->Fit("g1","","",yc-15,yc+15);
	yfp[i][j]=g1->GetParameter(1);	
	
        double bc=hb[i][j]->GetXaxis()->GetBinCenter(hb[i][j]->GetMaximumBin());
        hb[i][j]->Fit("g1","","",bc-0.025,bc+0.025);	
	bfp[i][j]=g1->GetParameter(1);		

	atgt[i][j]=26.67/1000.0*(2-i);
	btgt[i][j]=42.23/1000.0*(2-j);	

	
	ofile  << xfp[i][j] << " ";
	ofile  << afp[i][j] << " ";
	ofile  << yfp[i][j] << " ";
	ofile  << bfp[i][j] << " ";
	ofile  << atgt[i][j] << " ";
	ofile  << btgt[i][j] <<  std::endl;	
	
    }
      /*
    }else if(i==4){
      int j=2;
      ha[i][j]->Fit("g1");
      afp[i][j]=g1->GetParameter(1);
      hy[i][j]->Fit("g1");
      yfp[i][j]=g1->GetParameter(1);	
      hb[i][j]->Fit("g1");
      bfp[i][j]=g1->GetParameter(1);
      atgt[i][j]=26.67/1000.0*(2-i);
      btgt[i][j]=42.23/1000.0*(2-j);		
      ofile  << x << " ";
      ofile  << afp[i][j] << " ";
      ofile  << yfp[i][j] << " ";
      ofile  << bfp[i][j] << " ";
      ofile  << atgt[i][j] << " ";
      ofile  << btgt[i][j] <<  std::endl;	
      
    }else{
      for(int j=0;j<5;j++){
	ha[i][j]->Fit("g1");
	afp[i][j]=g1->GetParameter(1);
	hy[i][j]->Fit("g1");
	yfp[i][j]=g1->GetParameter(1);	
	hb[i][j]->Fit("g1");
	bfp[i][j]=g1->GetParameter(1);		
	atgt[i][j]=26.67/1000.0*(2-i);
	btgt[i][j]=42.23/1000.0*(2-j);	

	ofile  << x << " ";
	ofile  << afp[i][j] << " ";
	ofile  << yfp[i][j] << " ";
	ofile  << bfp[i][j] << " ";
	ofile  << atgt[i][j] << " ";
	ofile  << btgt[i][j] <<  std::endl;		
      }
      }*/
  }
  ofile.close();

}
