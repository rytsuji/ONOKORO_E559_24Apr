const int nFile=5;
const int OrderA=3;
const int OrderX=3;
const int SizeY=2;
int OrderY[SizeY]={0,1};
std::vector<std::vector<double>> x;
std::vector<std::vector<double>> a;
std::vector<std::vector<double>> y;
std::vector<std::vector<double>> b;
std::vector<std::vector<double>> a_tgt;
std::vector<std::vector<double>> b_tgt;
std::vector<std::vector<double>> bc;

const int nPrm=2+(OrderA+1)*(OrderX+1)*SizeY; //order of Y: 0,1,3

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data();



int b_gr(){


  read_data();
  std::cout <<  "****DEBUG****" << std::endl;
  TMinuit *min = new TMinuit(nPrm);// set number of parameters
  min->SetPrintLevel(1);
  int ierflg = 0;
  
  //Intialize of parameters
  double vstart[nPrm];
  for(int i=0;i<nPrm;i++){
    vstart[i] = 0.0;
  }
  //y=0, a=0
  vstart[0] = 0.00329459-0.0015856;
  vstart[1] = -3.32546e-06-1.07349e-06;
  vstart[2] = 4.55939e-09+8.10076e-08;
  vstart[3] = 2.0e-11;
  vstart[32] = -4.12212e-13;
  //y=0, a=1
  vstart[4] = 0.0352706-6.6337e-05-0.0199662;
  vstart[5] = 6.91772e-05;
  vstart[6] = 2.98205e-08;
  vstart[7] = 3.59195e-12;

  vstart[8] = 0.03;
  vstart[9] = 1.29474e-05;
  vstart[10] = 3.08099e-08;
  vstart[11] =7.33158e-11;

  vstart[12] = 0.2;
  vstart[13] = 0.000264272;
  vstart[14] = 6.28867e-07;
  vstart[15] = 1.49646e-09;
  //y=1, a=0
  vstart[16] = 0.0015759;
  vstart[17] = -3.08936e-07;
  vstart[18] = -1.93781e-10;
  vstart[19] = 2.05477e-14;  
  //y=1, a=1
  vstart[20] = 0.0269195;
  vstart[21] = 6.04194e-06;
  vstart[22] = -7.73104e-08;
  vstart[23] = -1.62723e-10;
  //y=0, a=2
  vstart[24] = 0.460607;
  vstart[25] = 0.00113621;
  vstart[26] = 6.05092e-07;
  vstart[27] = -1.18214e-09;

  vstart[28] = 0.0129673;
  vstart[29] = 3.0857e-05;
  vstart[30] = 7.34277e-08;
  vstart[31] = 1.7473e-10;

  
  //step width
  double step[nPrm];
  for(int i=0;i<nPrm;i++){
    if(vstart[i]>0){
      step[i] = fabs(vstart[i])*0.001;
    }else{
      step[i]=1.0e-15;
    }
  }

  //set limit of prm
  //ierflg=0 if no problems, >0 if MNPARM unable to implement definition
  for(int i=0;i<nPrm;i++){
    min->mnparm(i, Form("p%d",i), vstart[i], step[i], 0, 0, ierflg);
  }
  
  min->SetFCN(chi2);



  int migrad_stats = min->Migrad();
  migrad_stats = min->Migrad(); 
  
  TString oname="work/fp_gr/dat/fit_result.dat"; 
  ofstream ofile((std::string) oname);
  
  double par[nPrm]; //x0,x1,...,x4,a,xa,xxa,aa,xaa,xxaaa,...,xxaaaaa
  double par_err[nPrm];

  cout<<"**************************************"<<endl;
  for(int i=0;i<nPrm;i++){
    min->GetParameter(i,par[i],par_err[i]);
    cout<<"p" << i << ": "<< par[i] <<" +/- "<< par_err[i] <<endl;
    ofile << par[i] << " " << par_err[i] << std::endl;
  }
  ofile.close();

  TString oname_yaml="work/ang_gr/dat/gr_b.yaml"; 
  ofstream ofile_yaml((std::string) oname_yaml);
  
  for(int nY=0;nY<SizeY;nY++){
    for(int nA=0; nA < OrderA+1; nA++){
      for(int nX=0; nX < OrderX+1; nX++){
	if(nY==0 && nA==0 && nX==0) ofile_yaml << "#offset ";
	for(int i=0;i<nY;i++){
	  ofile_yaml << "y";
	}
	for(int i=0;i<nA;i++){
	  ofile_yaml << "a";
	}
	for(int i=0;i<nX;i++){
	  ofile_yaml << "x";
	}
	ofile_yaml << ": " << par[nY*(OrderA+1)*(OrderX+1)+(OrderA+1)*nA+nX] << std::endl;	
      }
    }
  }

  ofile_yaml << "xxxx: " <<  par[nPrm-2];;
  ofile_yaml << "aaaa: " <<  par[nPrm-1];;  
  ofile_yaml.close();
  
  TTree *tree = new TTree("tree","tree");
  tree->Branch("x",&x);
  tree->Branch("y",&y);  
  tree->Branch("a",&a);
  tree->Branch("b",&b);  
  tree->Branch("a_tgt",&a_tgt);
  tree->Branch("b_tgt",&b_tgt);
  tree->Branch("bc",&bc);
  bc.resize(5);
    
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      double val=0.0;
      for(int nY=0;nY<SizeY;nY++){
	for(int nA=0; nA < OrderA+1; nA++){
	  for(int nX=0; nX < OrderX+1; nX++){
	    val += par[nY*(OrderA+1)*(OrderX+1)+(OrderA+1)*nA+nX]*pow(y[i][j],OrderY[nY])*pow(a[i][j],nA)*pow(x[i][j],nX);	    	    
	  }
	}
      }
      val += par[nPrm-2]*pow(x[i][j],4);
      val += par[nPrm-1]*pow(a[i][j],4);      
      bc[i].push_back(val);
    }
  }
  
  tree->Fill();  
  delete min;    
  return 0;
}  



void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag){
  
  double chisq = 0;

  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      chisq = b_tgt[i][j];
      for(int nY=0;nY<SizeY;nY++){
	for(int nA=0; nA < OrderA+1; nA++){
	  for(int nX=0; nX < OrderX+1; nX++){
	    chisq -= par[nY*(OrderA+1)*(OrderX+1)+(OrderA+1)*nA+nX]*pow(y[i][j],OrderY[nY])*pow(a[i][j],nA)*pow(x[i][j],nX);
	  }
	}
      }      
      chisq -= par[nPrm-2]*pow(x[i][j],4);
      chisq -= par[nPrm-1]*pow(a[i][j],4);      
    }
  }

  chisq = pow(chisq,2.0);
  f = chisq;
  
}


void read_data(){
  x.resize(nFile);
  y.resize(nFile);
  a.resize(nFile);      
  b.resize(nFile);
  a_tgt.resize(nFile);
  b_tgt.resize(nFile);      
  std::string dir="work/ang_gr/dat/";
  std::string file[nFile]={"delta98.dat","delta99.dat","delta100.dat","delta101.dat","delta102.dat"};

   
  for(int iFile=0;iFile<nFile;iFile++){
    
    std::ifstream InFile(dir+file[iFile]);
    std::string InLine;
    while(getline(InFile,InLine)){
      std::string Str;
      std::vector<double> Val;
      stringstream SS(InLine);
      while(getline(SS, Str, ' ')){
	Val.push_back(std::stod(Str));
      }
      x[iFile].push_back(Val[0]);
      a[iFile].push_back(Val[1]);
      y[iFile].push_back(Val[2]);      
      b[iFile].push_back(Val[3]);
      a_tgt[iFile].push_back(Val[4]);
      b_tgt[iFile].push_back(Val[5]);                        
    }    
  }
}
  
