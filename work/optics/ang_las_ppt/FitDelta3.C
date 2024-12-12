{  
  //TFile *_file0 = TFile::Open("output/las/run5451129_3.root");
  TFile *_file0 = TFile::Open("output/sieve/run5451129_3.root");  
  ofstream ofile("work/ang_las_ppt/dat/fit3.dat");
  
  Double_t da_tgt=-16.0/606.5;                                                                                                                              
  Double_t db_tgt=25.0/606.5;  
  Double_t b_offset=2.288/1000.0;
  
  //X 
  double x=0;

  //Fit func
  TF1 *g1=new TF1("g1","gaus(0)",-200,200);    

  TCut bcut="abs(lfp.fB-lfp.GetY(-495.788)/2.608476e+03-0.0025)<0.0225";
  
  //A Y cut
  Double_t arange[6]={-0.2,-0.105,-0.035,0.035,0.107,0.2};
  Double_t yrange[6]={-100,-60,-10,25,80,95};
  
  TCut acut[5];
  TCut ycut[5];
  for(int i=0;i<5;i++){
    acut[i]=Form("lfp.fA>%e && lfp.fA<%e",arange[i],arange[i+1]);
    ycut[i]=Form("lfp.GetY(-495.788)>%e && lfp.GetY(-495.788)<%e",yrange[i],yrange[i+1]);    
  }
  TH1F *ha[5][5];
  TH1F *hy[5][5];
  TH1F *hb[5][5];
  
  //Draw
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      ha[i][j]=new TH1F(Form("ha[%d][%d]",i,j),Form("ha[%d][%d]",i,j),150,-0.3,0.3);
      hy[i][j]=new TH1F(Form("hy[%d][%d]",i,j),Form("hy[%d][%d]",i,j),150,-250,250);
      hb[i][j]=new TH1F(Form("hb[%d][%d]",i,j),Form("hb[%d][%d]",i,j),100,-0.2,0.2);
      TString drawa=Form("lfp.fA>>ha[%d][%d]",i,j);
      //TString drawy=Form("lfp.GetY(-495.788)>>hy[%d][%d]",i,j);
      TString drawy=Form("lfp.GetY()-10.132>>hy[%d][%d]",i,j);
      TString drawb=Form("lfp.fB>>hb[%d][%d]",i,j);
      tree->Draw(drawa,acut[i] && ycut[j] && bcut,"");
      tree->Draw(drawy,acut[i] && ycut[j] && bcut,"");
      tree->Draw(drawb,acut[i] && ycut[j] && bcut,"");

    }
  }
  
  
  
  //Fit


  Double_t afp[5][5];
  Double_t yfp[5][5];
  Double_t bfp[5][5];

  Double_t atgt[5][5];
  Double_t btgt[5][5];
  
  for(int i=0;i<5;i++){
    if(i==1 || i==2 ){
      for(int j=0;j<4;j++){

	double ac=ha[i][j]->GetXaxis()->GetBinCenter(ha[i][j]->GetMaximumBin());
	ha[i][j]->Fit("g1","","",ac-0.04,ac+0.04);
	afp[i][j]=g1->GetParameter(1);

	double yc=hy[i][j]->GetXaxis()->GetBinCenter(hy[i][j]->GetMaximumBin());
	hy[i][j]->Fit("g1","","",yc-15,yc+15);
	yfp[i][j]=g1->GetParameter(1);	

	double bc=hb[i][j]->GetXaxis()->GetBinCenter(hb[i][j]->GetMaximumBin());
	hb[i][j]->Fit("g1","","",bc-0.025,bc+0.025);
	bfp[i][j]=g1->GetParameter(1);		

        atgt[i][j]=da_tgt*(2-i);
        btgt[i][j]=db_tgt*(2-j)+b_offset;

	
	ofile  << x << " ";
	ofile  << afp[i][j] << " ";
	ofile  << yfp[i][j] << " ";
	ofile  << bfp[i][j] << " ";
	ofile  << atgt[i][j] << " ";
	ofile  << btgt[i][j] <<  std::endl;		
      }      
    }else{
      for(int j=1;j<4;j++){

	double ac=ha[i][j]->GetXaxis()->GetBinCenter(ha[i][j]->GetMaximumBin());
	ha[i][j]->Fit("g1","","",ac-0.04,ac+0.04);
	afp[i][j]=g1->GetParameter(1);

	double yc=hy[i][j]->GetXaxis()->GetBinCenter(hy[i][j]->GetMaximumBin());
	hy[i][j]->Fit("g1","","",yc-15,yc+15);
	yfp[i][j]=g1->GetParameter(1);	

	double bc=hb[i][j]->GetXaxis()->GetBinCenter(hb[i][j]->GetMaximumBin());
	hb[i][j]->Fit("g1","","",bc-0.025,bc+0.025);
	bfp[i][j]=g1->GetParameter(1);		

        atgt[i][j]=da_tgt*(2-i);
        btgt[i][j]=db_tgt*(2-j)+b_offset;
	
	ofile  << x << " ";
	ofile  << afp[i][j] << " ";
	ofile  << yfp[i][j] << " ";
	ofile  << bfp[i][j] << " ";
	ofile  << atgt[i][j] << " ";
	ofile  << btgt[i][j] <<  std::endl;		
      }
    }
  }
  ofile.close();
}
