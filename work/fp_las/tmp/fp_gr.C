const int nFile=5;
const int OrderA=4;
const int OrderX=3;
std::vector<std::vector<double>> x;
std::vector<std::vector<double>> a;
std::vector<std::vector<double>> xc;

const int nPrm=nFile+OrderA*(OrderX+1);

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data();



int fp_gr(){
  
  read_data();

  TMinuit *min = new TMinuit(nPrm);// set number of parameters
  min->SetPrintLevel(1);
  int ierflg = 0;
  
  //Intialize of parameters
  double vstart[nPrm];
  for(int i=0;i<nPrm;i++){
    vstart[i] = 0.0;
  }
  
  vstart[0] = -436.297;
  vstart[1] = -206.303;
  vstart[2] = 14.4776;
  vstart[3] = 223.403;
  vstart[4] = 423.634;
  
  //step width
  double step[nPrm];
  for(int i=0;i<nPrm;i++){
    if(abs(vstart[i])>0){
      step[i] = vstart[i]*0.001;
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
  
  TH1F *hist = new TH1F("hist","hist",2000,-1000,1000);
  TH2F *hxa = new TH2F("hxa","hxa",1000,-1000,1000,1000,-0.1,0.1);
  TH2F *hxa_raw = new TH2F("hxa_raw","hxa_raw",1000,-1000,1000,1000,-0.1,0.1);
  TTree *tree = new TTree("tree","tree");
  tree->Branch("x",&x);
  tree->Branch("a",&a);
  tree->Branch("xc",&xc);
  xc.resize(5);
    
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      double Xfp=x[i][j];
      for(int nA=0; nA < OrderA; nA++){
	for(int nX=0; nX < OrderX+1; nX++){
	  Xfp += par[5+nA*(OrderX+1)+nX]*pow(a[i][j],nA+1)*pow(x[i][j],nX);
	}
      }
      xc[i].push_back(Xfp-par[i]);
      hist->Fill(Xfp-par[i]);
      hxa->Fill(Xfp,a[i][j]);
      hxa_raw->Fill(x[i][j],a[i][j]);    
    }
  }
  
  //hist->Draw();
  tree->Fill();  
  delete min;    
  return 0;
}  



void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag){
  
  double chisq = 0;

  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      chisq = x[i][j]-par[i];
      for(int nA=0; nA < OrderA; nA++){
	for(int nX=0; nX < OrderX+1; nX++){
	  chisq += par[5+nA*(OrderX+1)+nX]*pow(a[i][j],nA+1)*pow(x[i][j],nX);
	}
      }
    }
  }
  chisq = pow(chisq,2.0);
  f = chisq;
  
}


void read_data(){
  x.resize(nFile);
  a.resize(nFile);    
  std::string dir="work/fp_gr/dat/";
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
      x[iFile].push_back(Val[1]);
      a[iFile].push_back(Val[2]);      
    }    
  }
}
  
