const int nFile=5;

std::vector<std::vector<double>> x;
std::vector<std::vector<double>> a;
std::vector<std::vector<double>> y;
std::vector<std::vector<double>> b;
std::vector<std::vector<double>> a_tgt;
std::vector<std::vector<double>> b_tgt;
std::vector<std::vector<double>> ac;

const int nPrm=15+4;

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data();

int a_las(){
  read_data();

  ac.resize(nFile);
  
  TMinuit *min = new TMinuit(nPrm);// set number of parameters
  min->SetPrintLevel(1);
  int ierflg = 0;
  
  //Intialize of parameters
  double vstart[nPrm];
  for(int i=0;i<nPrm;i++){
    vstart[i] = 0.0;
  }
  
  //step width
  double step[nPrm];
  for(int i=0;i<nPrm;i++){
      step[i]=1.0e-15;
  }
  //set limit of prm
  for(int i=0;i<nPrm;i++){
    min->mnparm(i, Form("p%d",i), vstart[i], step[i], 0, 0, ierflg);
  }
  
  min->SetFCN(chi2);

  int migrad_stats = min->Migrad();
  migrad_stats = min->Migrad(); 
  
  TString oname="work/ang_las_pph1/result/las_a.yaml"; 
  ofstream ofile((std::string) oname);
  
  double par[nPrm]; //x0,x1,...,x4,a,xa,xxa,aa,xaa,xxaaa,...,xxaaaaa
  double par_err[nPrm];

  cout<<"**************************************"<<endl;
  for(int i=0;i<nPrm;i++){
    min->GetParameter(i,par[i],par_err[i]);
    cout<<"p" << i << ": "<< par[i] <<" +/- "<< par_err[i] <<endl;
  }

  ofile  << "offset: " << par[0] << std::endl;
  ofile  << "x: " << par[1] << std::endl;
  ofile  << "a: " << par[2] << std::endl;
  ofile  << "xx: " << par[3] << std::endl;
  ofile  << "xa: " << par[4] << std::endl;
  ofile  << "aa: " << par[5] << std::endl;
  ofile  << "xxx: " << par[6] << std::endl;
  ofile  << "xxa: " << par[7] << std::endl;
  ofile  << "xaa: " << par[8] << std::endl;
  ofile  << "aaa: " << par[9] << std::endl;
  ofile  << "xxxx: " << par[10] << std::endl;
  ofile  << "xxxa: " << par[11] << std::endl;
  ofile  << "xxaa: " << par[12] << std::endl;  
  ofile  << "xaaa: " << par[13] << std::endl;
  ofile  << "aaaa: " << par[14] << std::endl;
  ofile  << "yy: "  << par[15] << std::endl;
  ofile  << "yyx: " << par[16] << std::endl;
  ofile  << "yya: " << par[17] << std::endl;
  //ofile  << "y: " << par[18] << std::endl;    



  /*
  ofile  << "yy: " << par[10] << std::endl;
  ofile  << "bb: " << par[11] << std::endl;
  ofile  << "yyx: " << par[12] << std::endl;
  ofile  << "yya: " << par[13] << std::endl;
  ofile  << "bbx: " << par[14] << std::endl;
  ofile  << "bba: " << par[15] << std::endl;
  ofile  << "yyxx: " << par[16] << std::endl;
  ofile  << "yyxa: " << par[17] << std::endl;
  ofile  << "yyaa: " << par[18] << std::endl;
  ofile  << "bbxx: " << par[16] << std::endl;
  ofile  << "bbxa: " << par[17] << std::endl;
  ofile  << "bbaa: " << par[18] << std::endl;
  ofile  << "xxxx: " << 0.0  << std::endl;    
  */
  ofile.close();

  TTree *tree = new TTree("tree","tree");
  tree->Branch("x",&x);
  tree->Branch("y",&y);  
  tree->Branch("a",&a);
  tree->Branch("b",&b);  
  tree->Branch("a_tgt",&a_tgt);
  tree->Branch("b_tgt",&b_tgt);
  tree->Branch("ac",&ac);

    
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      double val=0;
      val += par[0];
      val += par[1]*x[i][j];
      val += par[2]*a[i][j];
      val += par[3]*pow(x[i][j],2.0);
      val += par[4]*x[i][j]*a[i][j];
      val += par[5]*pow(a[i][j],2.0);
      val += par[6]*pow(x[i][j],3.0);
      val += par[7]*pow(x[i][j],2.0)*a[i][j];
      val += par[8]*pow(a[i][j],2.0)*x[i][j];                  
      val += par[9]*pow(a[i][j],3.0);
      val += par[10]*pow(x[i][j],4.0);
      val += par[11]*pow(x[i][j],3.0)*a[i][j];
      val += par[12]*pow(x[i][j],2.0)*pow(a[i][j],2.0);
      val += par[13]*pow(x[i][j],1.0)*pow(a[i][j],3.0);
      val += par[14]*pow(a[i][j],4.0);


      val += par[15]*pow(y[i][j],2.0);
      val += par[16]*pow(y[i][j],2.0)*x[i][j];
      val += par[17]*pow(y[i][j],2.0)*a[i][j];
      val += par[18]*pow(y[i][j],1.0);      
      /*
      val += par[10]*pow(y[i][j],2.0);
      val += par[11]*pow(b[i][j],2.0);
      val += par[12]*pow(y[i][j],2.0)*x[i][j];
      val += par[13]*pow(y[i][j],2.0)*a[i][j];
      val += par[14]*pow(b[i][j],2.0)*x[i][j];
      val += par[15]*pow(b[i][j],2.0)*a[i][j];
      val += par[16]*pow(y[i][j],2.0)*pow(x[i][j],2.0);
      val += par[17]*pow(y[i][j],2.0)*x[i][j]*a[i][j];
      val += par[18]*pow(y[i][j],2.0)*pow(a[i][j],2.0);
      val += par[19]*pow(b[i][j],2.0)*pow(x[i][j],2.0);
      val += par[20]*pow(b[i][j],2.0)*x[i][j]*a[i][j];
      val += par[21]*pow(b[i][j],2.0)*pow(a[i][j],2.0);                        */
      //val += par[16]*pow(x[i][j],4.0);                              
      ac[i].push_back(val);
    }
  }
  
  tree->Fill();  
  delete min;    
  return 0;
}  



void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag){
  
  double val = 0;
  double chisq = 0;  
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      val = -a_tgt[i][j];

      val += par[0];
      val += par[1]*x[i][j];
      val += par[2]*a[i][j];
      val += par[3]*pow(x[i][j],2.0);
      val += par[4]*x[i][j]*a[i][j];
      val += par[5]*pow(a[i][j],2.0);
      val += par[6]*pow(x[i][j],3.0);
      val += par[7]*pow(x[i][j],2.0)*a[i][j];
      val += par[8]*pow(a[i][j],2.0)*x[i][j];                  
      /*
      val += par[9]*pow(a[i][j],3.0);
      val += par[10]*pow(x[i][j],4.0);
      val += par[11]*pow(x[i][j],3.0)*a[i][j];
      val += par[12]*pow(x[i][j],2.0)*pow(a[i][j],2.0);
      val += par[13]*pow(x[i][j],1.0)*pow(a[i][j],3.0);
      val += par[14]*pow(a[i][j],4.0);
      */
      val += par[15]*pow(y[i][j],2.0);
      val += par[16]*pow(y[i][j],2.0)*x[i][j];
      val += par[17]*pow(y[i][j],2.0)*a[i][j];
      //val += par[18]*pow(y[i][j],1.0);      


      
      chisq += pow(val,2.0);
    }
  }
  f = chisq;
  
}


void read_data(){
  x.resize(nFile);
  y.resize(nFile);
  a.resize(nFile);      
  b.resize(nFile);
  a_tgt.resize(nFile);
  b_tgt.resize(nFile);      
  std::string dir="work/ang_las_pph1/dat/";
  //std::string file[nFile]={"fit1.dat","fit2.dat","fit3.dat","fit4.dat","fit5.dat","fit6.dat"};
  std::string file[nFile]={"fit1.dat","fit2.dat","fit3.dat","fit4.dat","fit5.dat"};

   
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
  
