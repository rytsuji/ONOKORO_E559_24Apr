{
  TFile *_file0 = TFile::Open("output/las/run1038.root");  
  TF1 *g1=new TF1("g1","gaus(0)",-200,200);    
  TF1 *g3=new TF1("g3","gaus(0)+gaus(3)+gaus(6)",-200,200);  
  TF1 *g5=new TF1("g5","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)",-200,200);
  
  //X Fit
  TH1F *hx=new TH1F("hx","hx",1000,-1000,1000);
  tree->Draw("lfp.fX>>hx","","");
  hx->Fit("g1","","",-300,-290);
  double x=g1->GetParameter(1);
  TCut xcut=Form("abs(lfp.fX-(%e))<5",x);
  
  //A Y cut
  Double_t arange[6]={-0.22,-0.15,-0.075,0.00,0.075,0.16};
  Double_t yrange[6]={-150,-65,-10,22.5,75,150};
  
  TCut acut[5];
  TCut ycut[5];
  for(int i=0;i<5;i++){
    acut[i]=Form("lfp.fA>%e && lfp.fA<%e",arange[i],arange[i+1]);
    ycut[i]=Form("lfp.fY>%e && lfp.fY<%e",yrange[i],yrange[i+1]);    
  }
  TH1F *ha[5][5];
  TH1F *hy[5][5];
  TH1F *hb[5][5];
  
  //Draw
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      ha[i][j]=new TH1F(Form("ha[%d][%d]",i,j),Form("ha[%d][%d]",i,j),200,-0.2,0.2);
      hy[i][j]=new TH1F(Form("hy[%d][%d]",i,j),Form("hy[%d][%d]",i,j),200,-200,200);
      hb[i][j]=new TH1F(Form("hb[%d][%d]",i,j),Form("hb[%d][%d]",i,j),200,-0.1,0.1);
      TString drawa=Form("lfp.fA>>ha[%d][%d]",i,j);
      TString drawy=Form("lfp.fY>>hy[%d][%d]",i,j);
      TString drawb=Form("lfp.fB>>hb[%d][%d]",i,j);
      tree->Draw(drawa,xcut && acut[i] && ycut[j],"");
      tree->Draw(drawy,xcut && acut[i] && ycut[j],"");
      tree->Draw(drawb,xcut && acut[i] && ycut[j],"");

    }
  }
  
  
  
  //Fit
  ofstream ofile("work/ang_las/dat/delta107dat");

  Double_t afp[5][5];
  Double_t yfp[5][5];
  Double_t bfp[5][5];

  Double_t atgt[5][5];
  Double_t btgt[5][5];
  
  for(int i=0;i<5;i++){
    if(i==0 || i==3){
      for(int j=1;j<4;j++){	
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
    }
  }

}
