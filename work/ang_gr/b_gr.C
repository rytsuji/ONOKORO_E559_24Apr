const int nFile=5;

const int MaxOrderTot=3;
const int OrderX=3;
const int OrderA=3;
const int OrderY=3;
const int OrderB=3;

std::vector<std::vector<double>> x;
std::vector<std::vector<double>> a;
std::vector<std::vector<double>> y;
std::vector<std::vector<double>> b;
std::vector<std::vector<double>> a_tgt;
std::vector<std::vector<double>> b_tgt;
std::vector<std::vector<double>> bc;

const int nPrm=27;

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
  
  TString oname="work/ang_gr/dat/gr_b.yaml"; 
  ofstream ofile((std::string) oname);
  
  double par[nPrm]; //x0,x1,...,x4,a,xa,xxa,aa,xaa,xxaaa,...,xxaaaaa
  double par_err[nPrm];

  cout<<"**************************************"<<endl;
  for(int i=0;i<nPrm;i++){
    min->GetParameter(i,par[i],par_err[i]);
    cout<<"p" << i << ": "<< par[i] <<" +/- "<< par_err[i] <<endl;
  }

  ofile  << "#offset:" << par[0] << std::endl;
  ofile  << "y: " << par[1] << std::endl;
  ofile  << "b: " << par[2] << std::endl;
  ofile  << "x: " << par[3] << std::endl;
  ofile  << "a: " << par[4] << std::endl;
  ofile  << "yx: " << par[5] << std::endl;
  ofile  << "ya: " << par[6] << std::endl;
  ofile  << "bx: " << par[7] << std::endl;
  ofile  << "ba: " << par[8] << std::endl;
  ofile  << "xx: " << par[9] << std::endl;
  ofile  << "xa: " << par[10] << std::endl;
  ofile  << "aa: " << par[11] << std::endl;
  ofile  << "yyy: " << par[12] << std::endl;
  ofile  << "yyb: " << par[13] << std::endl;
  ofile  << "ybb: " << par[14] << std::endl;
  ofile  << "yxx: " << par[15] << std::endl;
  ofile  << "yxa: " << par[16] << std::endl;
  ofile  << "yaa: " << par[17] << std::endl;
  ofile  << "bbb: " << par[18] << std::endl;  
  ofile  << "bxx: " << par[19] << std::endl;
  ofile  << "bxa: " << par[20] << std::endl;
  ofile  << "baa: " << par[21] << std::endl;
  ofile  << "xxx: " << par[22] << std::endl;
  ofile  << "xxa: " << par[23] << std::endl;
  ofile  << "xaa: " << par[24] << std::endl;
  ofile  << "aaa: " << par[25] << std::endl;
  ofile  << "xxxx: " << par[26] << std::endl;                          
  
  
  ofile.close();

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
      double val=0;
      val += par[0];
      val += par[1]*y[i][j];
      val += par[2]*b[i][j];  
      val += par[3]*x[i][j];
      val += par[4]*a[i][j];
      val += par[5]*y[i][j]*x[i][j];
      val += par[6]*y[i][j]*a[i][j];
      val += par[7]*b[i][j]*x[i][j];
      val += par[8]*b[i][j]*a[i][j];
      
      val += par[9]*x[i][j]*x[i][j];
      val += par[10]*x[i][j]*a[i][j];
      val += par[11]*a[i][j]*a[i][j];                    

      val += par[12]*pow(y[i][j],3.0);
      val += par[13]*b[i][j]*pow(y[i][j],2.0);
      val += par[14]*y[i][j]*pow(b[i][j],2.0);      
      val += par[15]*y[i][j]*pow(x[i][j],2.0);
      val += par[16]*y[i][j]*x[i][j]*a[i][j];      
      val += par[17]*y[i][j]*pow(a[i][j],2.0);
      val += par[18]*pow(b[i][j],3.0);
      val += par[19]*b[i][j]*pow(x[i][j],2.0);
      val += par[20]*b[i][j]*x[i][j]*a[i][j];      
      val += par[21]*b[i][j]*pow(a[i][j],2.0);

      val += par[22]*pow(x[i][j],3.0);
      val += par[23]*pow(x[i][j],2.0)*a[i][j];
      val += par[24]*pow(a[i][j],2.0)*x[i][j];
      val += par[25]*pow(a[i][j],3.0);
      val += par[26]*pow(x[i][j],4.0);
      bc[i].push_back(val);
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
      val = -b_tgt[i][j];

      val += par[0];
      val += par[1]*y[i][j];
      val += par[2]*b[i][j];  




      //val += par[4]*a[i][j];

      val += par[5]*y[i][j]*x[i][j];
      val += par[6]*y[i][j]*a[i][j];
      val += par[7]*b[i][j]*x[i][j];
      val += par[8]*b[i][j]*a[i][j];


      //val += par[10]*x[i][j]*a[i][j];
      //val += par[11]*a[i][j]*a[i][j];                    

      val += par[12]*pow(y[i][j],3.0);
      val += par[13]*b[i][j]*pow(y[i][j],2.0);
      val += par[14]*y[i][j]*pow(b[i][j],2.0);      
      val += par[15]*y[i][j]*pow(x[i][j],2.0);
      val += par[16]*y[i][j]*x[i][j]*a[i][j];      
      val += par[17]*y[i][j]*pow(a[i][j],2.0);
      val += par[18]*pow(b[i][j],3.0);
      val += par[19]*b[i][j]*pow(x[i][j],2.0);
      val += par[20]*b[i][j]*x[i][j]*a[i][j];      
      val += par[21]*b[i][j]*pow(a[i][j],2.0);


      val += par[3]*x[i][j];
      val += par[9]*x[i][j]*x[i][j];      
      val += par[22]*pow(x[i][j],3.0);
      val += par[26]*pow(x[i][j],4.0);

      
      //val += par[23]*pow(x[i][j],2.0)*a[i][j];
      //val += par[24]*pow(a[i][j],2.0)*x[i][j];
      //val += par[25]*pow(a[i][j],3.0);



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
  
