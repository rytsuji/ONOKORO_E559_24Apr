//const int nFile=6;
const int nFile=5;

std::vector<std::vector<double>> x;
std::vector<std::vector<double>> a;
std::vector<std::vector<double>> y;
std::vector<std::vector<double>> b;
std::vector<std::vector<double>> a_tgt;
std::vector<std::vector<double>> b_tgt;
std::vector<std::vector<double>> bc;

const int nPrm=28;

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data();

int b_las(){
  read_data();
  //std::cout <<  "****DEBUG****" << std::endl;
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
  
  TString oname="work/ang_las_pph/result/las_b.yaml"; 
  ofstream ofile((std::string) oname);
  
  double par[nPrm]; //x0,x1,...,x4,a,xa,xxa,aa,xaa,xxaaa,...,xxaaaaa
  double par_err[nPrm];

  cout<<"**************************************"<<endl;
  for(int i=0;i<nPrm;i++){
    min->GetParameter(i,par[i],par_err[i]);
    cout<<"p" << i << ": "<< par[i] <<" +/- "<< par_err[i] <<endl;
  }

  ofile  << "offset: " << par[0] << std::endl;
  ofile  << "y: " << par[1] << std::endl;
  ofile  << "b: " << par[2] << std::endl;
  ofile  << "yx: " << par[3] << std::endl;
  ofile  << "ya: " << par[4] << std::endl;
  ofile  << "yxx: " << par[5] << std::endl;
  ofile  << "yxa: " << par[6] << std::endl;
  ofile  << "yaa: " << par[7] << std::endl;
  ofile  << "yxxx: " << par[8] << std::endl;
  ofile  << "yxxa: " << par[9] << std::endl;
  ofile  << "yxaa: " << par[10] << std::endl;
  ofile  << "yaaa: " << par[11] << std::endl;  
  ofile  << "bx: " << par[12] << std::endl;
  ofile  << "ba: " << par[13] << std::endl;
  ofile  << "yyy: " << par[14] << std::endl;
  ofile  << "yyyx: " << par[15] << std::endl;
  ofile  << "yyya: " << par[16] << std::endl;
  ofile  << "yyyxx: " << par[17] << std::endl;
  ofile  << "yyyxa: " << par[18] << std::endl;
  ofile  << "yyyaa: " << par[19] << std::endl;

  //ofile  << "bxx: " << par[20] << std::endl;
  //ofile  << "bxa: " << par[21] << std::endl;
  //ofile  << "baa: " << par[22] << std::endl;
  ofile  << "x: " << par[23] << std::endl;
  ofile  << "xx: " << par[24] << std::endl;
  ofile  << "a: " << par[25] << std::endl;
  ofile  << "aa: " << par[26] << std::endl;
  //ofile  << "yy: " << par[27] << std::endl;              
  

  
  
  ofile.close();

  TTree *tree = new TTree("tree","tree");
  tree->Branch("x",&x);
  tree->Branch("y",&y);  
  tree->Branch("a",&a);
  tree->Branch("b",&b);  
  tree->Branch("a_tgt",&a_tgt);
  tree->Branch("b_tgt",&b_tgt);
  tree->Branch("bc",&bc);
  bc.resize(nFile);
    
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      double val=0;

      val = 0.0;

      val += par[0];
      val += par[1]*y[i][j];
      val += par[2]*b[i][j];  
      val += par[3]*y[i][j]*x[i][j];
      val += par[4]*y[i][j]*a[i][j];
      val += par[5]*y[i][j]*x[i][j]*x[i][j];
      val += par[6]*y[i][j]*a[i][j]*x[i][j];;      
      val += par[7]*y[i][j]*a[i][j]*a[i][j];



      val += par[8]*y[i][j]*pow(x[i][j],3.0);
      val += par[9]*y[i][j]*pow(x[i][j],2.0)*pow(a[i][j],1.0);
      val += par[10]*y[i][j]*pow(x[i][j],1.0)*pow(a[i][j],2.0);
      val += par[11]*y[i][j]*pow(x[i][j],0.0)*pow(a[i][j],3.0);            

      
      val += par[12]*b[i][j]*x[i][j];                 
      val += par[13]*b[i][j]*a[i][j];

      val += par[14]*pow(y[i][j],3.0);
      val += par[15]*pow(y[i][j],3.0)*x[i][j];
      val += par[16]*pow(y[i][j],3.0)*a[i][j];

      
      val += par[17]*pow(y[i][j],3.0)*x[i][j]*x[i][j];
      val += par[18]*pow(y[i][j],3.0)*x[i][j]*a[i][j];
      val += par[19]*pow(y[i][j],3.0)*a[i][j]*a[i][j];

      val += par[20]*b[i][j]*x[i][j]*x[i][j];                 
      val += par[21]*b[i][j]*a[i][j]*x[i][j];
      val += par[22]*b[i][j]*a[i][j]*a[i][j];      

      val += par[23]*pow(x[i][j],1.0);
      val += par[24]*pow(x[i][j],2.0);
      val += par[25]*pow(a[i][j],1.0);
      val += par[26]*pow(a[i][j],2.0);

      val += par[27]*pow(y[i][j],2.0);

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
      //val += par[2]*b[i][j];  
      val += par[3]*y[i][j]*x[i][j];
      val += par[4]*y[i][j]*a[i][j];
      val += par[5]*y[i][j]*x[i][j]*x[i][j];
      val += par[6]*y[i][j]*a[i][j]*x[i][j];;      
      val += par[7]*y[i][j]*a[i][j]*a[i][j];

      val += par[8]*y[i][j]*pow(x[i][j],3.0);
      val += par[9]*y[i][j]*pow(x[i][j],2.0)*pow(a[i][j],1.0);
      val += par[10]*y[i][j]*pow(x[i][j],1.0)*pow(a[i][j],2.0);
      val += par[11]*y[i][j]*pow(x[i][j],0.0)*pow(a[i][j],3.0);            

      
      val += par[12]*b[i][j]*x[i][j];                 
      val += par[13]*b[i][j]*a[i][j];

      val += par[14]*pow(y[i][j],3.0);
      val += par[15]*pow(y[i][j],3.0)*x[i][j];
      val += par[16]*pow(y[i][j],3.0)*a[i][j];

      val += par[17]*pow(y[i][j],3.0)*x[i][j]*x[i][j];
      val += par[18]*pow(y[i][j],3.0)*x[i][j]*a[i][j];
      val += par[19]*pow(y[i][j],3.0)*a[i][j]*a[i][j];
      
      //val += par[20]*b[i][j]*x[i][j]*x[i][j];                 
      //val += par[21]*b[i][j]*a[i][j]*x[i][j];
      //val += par[22]*b[i][j]*a[i][j]*a[i][j];      

      val += par[23]*pow(x[i][j],1.0);
      val += par[24]*pow(x[i][j],2.0);
      val += par[25]*pow(a[i][j],1.0);
      val += par[26]*pow(a[i][j],2.0);

      //val += par[27]*pow(y[i][j],2.0);

      //if(fabs(b_tgt[i][j])>0.08) val=val*2.0;
   
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
  std::string dir="work/ang_las_pph/dat/";
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
      //if(fabs(Val[5])<0.05){
      x[iFile].push_back(Val[0]);
      a[iFile].push_back(Val[1]);
      y[iFile].push_back(Val[2]);      
      b[iFile].push_back(Val[3]);
      a_tgt[iFile].push_back(Val[4]);
      b_tgt[iFile].push_back(Val[5]);
      //}
    }    
  }
}
  
