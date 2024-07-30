const int nFile=5;
const int OrderA=4;
const int OrderX=3;
std::vector<std::vector<double>> x;
std::vector<std::vector<double>> xc;
std::vector<std::vector<double>> a;

const int nPrm=nFile+OrderA*(OrderX+1);

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void chi2_itr(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data();



int fp_gr_itr(){
  
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
  
  vstart[5] =  55.5751+1.5227;
  vstart[6] = -0.767544+0.0106579;
  vstart[7] = -0.00205144+0.000158437;
  vstart[8] = -3.78802e-06+3.60424e-07;
  
  vstart[8+OrderX-2] = 4853.13+126.504;
  vstart[9+OrderX-2] = 18.6104-7.87556;
  vstart[10+OrderX-2] = 0.0511677+0.00608428;
  vstart[11+OrderX-2] = -6.34781e-07+6.89372e-05;  
  
  vstart[11+2*(OrderX-2)] = -51300.1-4413.12;
  vstart[12+2*(OrderX-2)] = -380.721+56.7712;
  vstart[13+2*(OrderX-2)] = -0.279834-0.210615;
  vstart[14+2*(OrderX-2)] = -9.26688e-06-0.000495799;  
  
  vstart[14+3*(OrderX-2)] = 980211+70019.6;
  vstart[15+3*(OrderX-2)] = -130.854+2126.15;
  vstart[16+3*(OrderX-2)] = 1.10331-0.541118;
  vstart[17+3*(OrderX-2)] = 0.00885869-0.0105815;
  
  //step width
  double step[nPrm];
  for(int i=0;i<nPrm;i++){
    if(vstart[i]>0){
      step[i] = vstart[i]*0.001;
    }else{
      step[i]=0.00001;
    }
  }


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
  delete min;


  //Iteation
  TMinuit *min_itr = new TMinuit(nPrm);// set number of parameters
  min_itr->SetPrintLevel(1);
  for(int i=0;i<nPrm;i++){
    vstart[i]=0;
    step[i]=0.00001;
  }
  for(int i=0;i<nPrm;i++){
    min_itr->mnparm(i, Form("p%d",i), vstart[i], step[i], 0, 0, ierflg);
  }

  min_itr->SetFCN(chi2_itr);
  int migrad_stats_itr = min_itr->Migrad();
  migrad_stats_itr = min_itr->Migrad();  

  TString oname_itr="work/fp_gr/dat/fit_result_itr.dat"; 
  ofstream ofile_itr((std::string) oname_itr);  
  double par_itr[nPrm]; //x0,x1,...,x4,a,xa,xxa,aa,xaa,xxaaa,...,xxaaaaa
  double par_err_itr[nPrm];
  cout<<"**************************************"<<endl;
  for(int i=0;i<nPrm;i++){
    min->GetParameter(i,par_itr[i],par_err_itr[i]);
    cout<<"p" << i << ": "<< par_itr[i] <<" +/- "<< par_err_itr[i] <<endl;
    ofile_itr << par_itr[i] << " " << par_err_itr[i] << std::endl;
  }
  ofile_itr.close();

  TString oname_matrix="work/fp_gr/dat/matrix.yaml"; 
  ofstream ofile_matrix((std::string) oname_matrix);  
  for(int nA=0; nA < OrderA; nA++){
    for(int nX=0; nX < OrderX+1; nX++){
      if(nX+nA<5){
	if(nA==0 && nX==0){
	  ofile_matrix << "#";
	}
	for(int i=0;i<nX;i++){
	  ofile_matrix << "x";
	}
	for(int i=0;i<nA+1;i++){
	  ofile_matrix << "a";
	}
	ofile_matrix << ": " << par[5+nA*(OrderX+1)+nX]+par_itr[5+nA*(OrderX+1)+nX] << std::endl;
      }
    }
  }
  ofile_matrix.close();

  TH1F *hist_itr = new TH1F("hist_itr","hist_itr",2000,-1000,1000);
  TH2F *hxa_itr = new TH2F("hxa_itr","hxa_itr",10000,-1000,1000,1000,-0.1,0.1);
  TH2F *hax_itr = new TH2F("hax_itr","hax_itr",1000,-0.1,0.1,5000,-1000,1000);  

  TTree *tree = new TTree("tree","tree");

  tree->Branch("x",&x);
  tree->Branch("a",&a);
  tree->Branch("xc",&xc);   
  
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      double Xfp=xc[i][j];
      for(int nA=0; nA < OrderA; nA++){
	for(int nX=0; nX < OrderX+1; nX++){
	  if(nX+nA<5){
	    Xfp += par_itr[5+nA*(OrderX+1)+nX]*pow(a[i][j],nA+1)*pow(x[i][j],nX);
	  }
	}
      }
      hist_itr->Fill(Xfp-par_itr[i]);
      hxa_itr->Fill(Xfp+par[i],a[i][j]);
      hax_itr->Fill(a[i][j],Xfp+par[i]);      
    }
  }
  tree->Fill();
  delete min_itr;
  
  return 0;
}  



void chi2_itr(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag){
  
  double chisq = 0;

  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      chisq = xc[i][j]-par[i];
      for(int nA=0; nA < OrderA; nA++){
	for(int nX=0; nX < OrderX+1; nX++){
	  if(nX+nA<5){
	    chisq += par[5+nA*(OrderX+1)+nX]*pow(a[i][j],nA+1)*pow(x[i][j],nX);
	  }
	}
      }
    }
  }
  chisq = pow(chisq,2.0);
  f = chisq;
  
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
  
