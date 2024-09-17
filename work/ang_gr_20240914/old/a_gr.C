const int nFile=5;
const int OrderA=3;
const int OrderX=3;
std::vector<std::vector<double>> x;
std::vector<std::vector<double>> a;
std::vector<std::vector<double>> y;
std::vector<std::vector<double>> b;
std::vector<std::vector<double>> a_tgt;
std::vector<std::vector<double>> b_tgt;
std::vector<std::vector<double>> ac;

const int nPrm=(OrderA+1)*(OrderX+1)+4+4+1;

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data();



int a_gr(){


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
  
  vstart[0] = 0.00164912-0.000248527-0.000181905+0.000226985;
  vstart[1] = 2.2632e-05-1.3074e-06-1.06027e-06;
  vstart[2] = 6.17563e-09-4.77528e-10-9.08655e-10;
  vstart[3] = 9.74772e-12-1.28381e-12-4.33673e-13;
  vstart[24] = 5.57824e-14 ;

  vstart[4+(OrderX-3)] = -0.444052+0.0322489;
  vstart[5+(OrderX-3)] = -7.4859e-05;
  vstart[6+(OrderX-3)] = 7.05863e-09;
  vstart[7+(OrderX-3)] = 9.92124e-11;

  vstart[8+(OrderX-3)*2] = 0.552954-0.313674;
  vstart[9+(OrderX-3)*2] = 0.000364687; 
  vstart[10+(OrderX-3)*2] = -2.26123e-08;
  vstart[11+(OrderX-3)*2] = 1.36968e-09;

  vstart[12+(OrderX-3)*3] = -2.72301-7.71848;
  vstart[13+(OrderX-3)*3] = 0.00593665;
  vstart[14+(OrderX-3)*3] = 1.06079e-05;
  vstart[15+(OrderX-3)*3] = -1.63986e-09;

  vstart[16] = 1.5e-05-6.46624e-06;

  vstart[20] = 7.19913e-07-6.49507e-07-8.31127e-07;

  
  
  
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

  TString oname_yaml="work/fp_gr/dat/gr_a.yaml"; 
  ofstream ofile_yaml((std::string) oname_yaml);
  for(int nA=0; nA < OrderA+1; nA++){
    for(int nX=0; nX < OrderX+1; nX++){      

      if(nA==0 && nX==0) ofile_yaml << "#offset";
      for(int i=0; i<nA ;i++){
	ofile_yaml << "a" ;
      }
      for(int j=0; j<nX ;j++){
	ofile_yaml << "x" ; 
      }
      ofile_yaml << ": " << par[(OrderA+1)*nA+nX] << std::endl;
    }
  }

  ofile_yaml << "y: " << par[(OrderA+1)*(OrderX+1)] << std::endl;
  ofile_yaml << "yx: " << par[(OrderA+1)*(OrderX+1)+1] << std::endl;
  ofile_yaml << "ya: " << par[(OrderA+1)*(OrderX+1)+2] << std::endl;
  ofile_yaml << "yxa: " << par[(OrderA+1)*(OrderX+1)+3] << std::endl;

  ofile_yaml << "yy: " << par[(OrderA+1)*(OrderX+1)+4] << std::endl;
  ofile_yaml << "yyx: " << par[(OrderA+1)*(OrderX+1)+5] << std::endl;
  ofile_yaml << "yya: " << par[(OrderA+1)*(OrderX+1)+6] << std::endl;
  ofile_yaml << "yyxa: " << par[(OrderA+1)*(OrderX+1)+7] << std::endl;  
  ofile_yaml.close();
  
  TTree *tree = new TTree("tree","tree");
  tree->Branch("x",&x);
  tree->Branch("y",&y);  
  tree->Branch("a",&a);
  tree->Branch("b",&b);  
  tree->Branch("a_tgt",&a_tgt);
  tree->Branch("b_tgt",&b_tgt);
  tree->Branch("ac",&ac);
  ac.resize(5);
    
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      double val=0.0;
      for(int nA=0; nA < OrderA+1; nA++){
        for(int nX=0; nX < OrderX+1; nX++){
          val += par[(OrderA+1)*nA+nX]*pow(a[i][j],nA)*pow(x[i][j],nX);
        }
      }
      val += y[i][j]*(par[(OrderA+1)*(OrderX+1)]+par[(OrderA+1)*(OrderX+1)+1]*x[i][j]+par[(OrderA+1)*(OrderX+1)+2]*a[i][j]+par[(OrderA+1)*(OrderX+1)+3]*a[i][j]*x[i][j]);

      val += y[i][j]*y[i][j]*(par[(OrderA+1)*(OrderX+1)+4]+par[(OrderA+1)*(OrderX+1)+5]*x[i][j]+par[(OrderA+1)*(OrderX+1)+6]*a[i][j]+par[(OrderA+1)*(OrderX+1)+7]*a[i][j]*x[i][j]);
      //val += par[(OrderA+1)*(OrderX+1)+8]*pow(x[i][j],4);
      ac[i].push_back(val);
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
      chisq = a_tgt[i][j];
      for(int nA=0; nA < OrderA+1; nA++){
	for(int nX=0; nX < OrderX+1; nX++){
	  chisq -= par[(OrderA+1)*nA+nX]*pow(a[i][j],nA)*pow(x[i][j],nX);
	}
      }
      chisq -= y[i][j]*(par[(OrderA+1)*(OrderX+1)]+par[(OrderA+1)*(OrderX+1)+1]*x[i][j]+par[(OrderA+1)*(OrderX+1)+2]*a[i][j]+par[(OrderA+1)*(OrderX+1)+3]*a[i][j]*x[i][j]);

      chisq -= y[i][j]*y[i][j]*(par[(OrderA+1)*(OrderX+1)+4]+par[(OrderA+1)*(OrderX+1)+5]*x[i][j]+par[(OrderA+1)*(OrderX+1)+6]*a[i][j]+par[(OrderA+1)*(OrderX+1)+7]*a[i][j]*x[i][j]);

      //chisq += par[(OrderA+1)*(OrderX+1)+8]*pow(x[i][j],4);
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
  
