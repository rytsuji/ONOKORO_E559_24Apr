const int nFile=5;
const int OrderA=4;
const int OrderX=4;
const int MaxOrder=8;

std::vector<std::vector<double>> x;
std::vector<std::vector<double>> xc;
std::vector<std::vector<double>> a;

const int nPrm=nFile+OrderA*(OrderX+1);

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void chi2_itr(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data();



int fp_las(){
  
  read_data();
  
  TMinuit *min = new TMinuit(nPrm);// set number of parameters
  min->SetPrintLevel(1);
  int ierflg = 0;
  
  //Intialize of parameters
  double vstart[nPrm];
  for(int i=0;i<nPrm;i++){
    vstart[i] = 0.0;
  }


  
  vstart[0] = 353.326;
  vstart[1] = 166.146;
  vstart[2] = -4.40224;
  vstart[3] = -159.273;
  vstart[4] = -300.444;
  
  vstart[5] = 0.0;
  vstart[6] = 0.113941;
  vstart[7] = -0.000536527;
  vstart[8] = -2.05629e-07;

  vstart[9] = 819.909+81.9132-148.236;
  vstart[10] = 1.11371;
  vstart[11] = 0.000950292;
  vstart[12] = -1.21413e-06;

  
  vstart[13] = 673.769-1799.1+842.288;
  vstart[14] = -3.23079;
  vstart[15] = 0.00399174;
  vstart[16] = 2.06366e-05;
  
  vstart[5+OrderA*(OrderX+1)]=0.0;

  /*
  vstart[20] = 6646.25;
  vstart[21] = -6.54664;
  vstart[22] = -0.294783;
  vstart[23] = -3.67499e-05;
  vstart[24] = 1.79768e-06;
  */
  for(int nA=0; nA < OrderA; nA++){
    for(int nX=0; nX < OrderX+1; nX++){
      if(nX+nA>MaxOrder){
	vstart[5+nA*(OrderX+1)+nX]=0.0;
      }
    }
  }

  
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

  //min->FixParameter(5);
  
  min->SetFCN(chi2);
  
  int migrad_stats = min->Migrad();
  
  TString oname="work/fp_las/result/fit_result1.dat"; 
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

  
  TH1F *hist = new TH1F("hist","hist",200,-20,20);
  TH2F *hxa = new TH2F("hxa","hxa",1000,-1000,1000,1000,-0.3,0.3);
  TH2F *hxa_raw = new TH2F("hxa_raw","hxa_raw",1000,-1000,1000,1000,-0.3,0.3);


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

  //min_itr->FixParameter(5);

  min_itr->SetFCN(chi2_itr);
  int migrad_stats_itr = min_itr->Migrad();
  migrad_stats_itr = min_itr->Migrad();  

  TString oname_itr="work/fp_las/result/fit_result2.dat"; 
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

  TString oname_matrix="work/fp_las/result/fp_las.yaml"; 
  ofstream ofile_matrix((std::string) oname_matrix);  
  for(int nA=0; nA < OrderA; nA++){
    for(int nX=0; nX < OrderX+1; nX++){
      if(nX+nA<MaxOrder+1){
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

  TH1F *hist_itr = new TH1F("hist_itr","hist_itr",200,-20,20);
  TH2F *hxa_itr = new TH2F("hxa_itr","hxa_itr",1000,-1000,1000,1000,-0.3,0.3);
  TH2F *hax_itr = new TH2F("hax_itr","hax_itr",1000,-0.3,0.3,5000,-1000,1000);  

  TTree *tree = new TTree("tree","tree");

  tree->Branch("x",&x);
  tree->Branch("a",&a);
  tree->Branch("xc",&xc);   
  
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x[i].size(); j++){
      double Xfp=xc[i][j];
      for(int nA=0; nA < OrderA; nA++){
	for(int nX=0; nX < OrderX+1; nX++){
	  if(nX+nA<MaxOrder+1){
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
	  if(nX+nA<MaxOrder+1){
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
  std::string dir="work/fp_las/dat/";
  std::string file[nFile]={"delta93.dat","delta96.5.dat","delta100.dat","delta103.5.dat","delta107.dat"};

   
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
  
