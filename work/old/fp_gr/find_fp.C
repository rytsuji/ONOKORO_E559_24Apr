std::vector<double> delta;
std::vector<double> x;
std::vector<double> a;


void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data(TString input);


int find_fp(){
  
  const int n_prm=7+5;
  read_data("dat/fp_gr.dat");

  TMinuit *min = new TMinuit(n_prm);// set number of parameters
  min->SetPrintLevel(1);
  min->SetFCN(chi2);
  int ierflg = 0;
  
  //Intialize of parameters
  double vstart[n_prm];
  vstart[0]  = 0.0; // offset of X

  vstart[1]  = -116.32694; // (A)
  vstart[2]  = -0.571705; // (XA)
  vstart[3]  = -0.000605274; // (XXA)

  vstart[4]  = 4155.18; // (AA)
  vstart[5]  = 2.32544; // (XAA)
  vstart[6]  =  0.0442343; // (XXAA)

  vstart[7]=420.0;
  vstart[8]=210.0;
  vstart[9]=0.0;
  vstart[10]=-230.0;
  vstart[11]=-460.0;

  
  //step width
  double step[n_prm];
  for(int i=0;i<n_prm;i++){
    step[i] = 0.001;
  }

  //set limit of prm
  //ierflg=0 if no problems, >0 if MNPARM unable to implement definition
  for(int i=0;i<n_prm;i++){
    min->mnparm(i, Form("p%d",i), vstart[i], step[i], 0, 0, ierflg);
  }
  
  
  double arglist[10];
  
  //1σを与えるカイ2乗値の増分を設定
  arglist[0] = 3.53;//1パラメータ:1.0, 2パラメータ:2.30
  min->mnexcm("SET ERR", arglist, 1, ierflg);


  arglist[0] = 1000;
  arglist[1] = 1;
  min->mnexcm("MIGRAD", arglist, 2, ierflg);
  
  
  TString oname="fit_result.dat"; 
  ofstream ofile((std::string) oname);
  
  double par[n_prm];
  double par_err[n_prm];

  cout<<"**************************************"<<endl;
  for(int i=0;i<n_prm;i++){
    min->GetParameter(i,par[i],par_err[i]);
    cout<<"p" << i << ": "<< par[i] <<" +/- "<< par_err[i] <<endl;    
  }
  ofile << "#x0: " << par[0] << " #err = " << par_err[0] << endl;

  ofile << "a: "  << par[1] << " #err = " << par_err[1] << endl;
  ofile << "xa: "  << par[2] << " #err = " << par_err[2] << endl;
  ofile << "xxa: "  << par[3] << " #err = " << par_err[3] << endl;

  ofile << "aa: "  << par[4] << " #err = " << par_err[4] << endl;
  ofile << "xaa: "  << par[5] << " #err = " << par_err[5] << endl;
  ofile << "xxaa: "  << par[6] << " #err = " << par_err[6] << endl;
  
  ofile.close();
  
  TH1F *hist = new TH1F("hist","hist",200,-1000,1000);
  TH1F *ht = new TH1F("ht","ht",200,-0.001,0.001);
  TH1F *hx1d = new TH1F("hx1d","hx1d",500,-1000,1000);
  TH2F *hx = new TH2F("hx","hx",1000,-750,750,200,-1000,1000);
  TH2F *hxd = new TH2F("hxd","hxd",1000,-750,750,200,-0.05,0.05);
  TH2F *ha = new TH2F("ha","ha",1000,-1,1,200,-1000,1000);
  TH2F *hax_raw= new TH2F("hax_raw","hax_raw",1000,-0.1,0.1,2000,-1000,1000);
  TH2F *hax= new TH2F("hax","hax",1000,-0.1,0.1,2000,-1000,1000);
  TH2F *hd = new TH2F("hd","hd",1000,-0.05,0.05,1000,-0.05,0.05);
  int loop =  delta.size();
  
  for(int i=0;i<loop;i++){

    double func = 0;
    func = (x[i]-par[0]);
    func += par[1]*pow(a[i],1.0)
      +par[2]*(a[i])*pow(x[i]-par[0],1.0)
      +par[3]*(a[i])*pow(x[i]-par[0],2.0);
    func += par[4]*pow(a[i],2.0)
      +par[5]*pow(a[i],2.0)*pow(x[i]-par[0],1.0)
      +par[6]*pow(a[i],2.0)*pow(x[i]-par[0],2.0);

    int target=2 + (int) delta[i]/0.01;
    

    

    hist->Fill(par[target]-func);
    hx->Fill(x[i],par[target]-func);
    ha->Fill(a[i],par[target]);
  }
  
  hist->Draw();
  
  delete min;
  
  return 0;
}  



void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag){
  int loop =  delta.size();
  
  double chisq = 0;

  for(int i=0; i<loop; i++){
    double func = 0;
    func = (x[i]-par[0]);
    func += par[1]*pow(a[i],1.0)
      +par[2]*(a[i])*pow(x[i]-par[0],1.0)
      +par[3]*(a[i])*pow(x[i]-par[0],2.0);
    func += par[4]*pow(a[i],2.0)
      +par[5]*pow(a[i],2.0)*pow(x[i]-par[0],1.0)
      +par[6]*pow(a[i],2.0)*pow(x[i]-par[0],2.0);

    int target=2 + (int) delta[i]/0.01;
    

    chisq += pow(par[target]-func,2.0);
  }
  
  f = chisq;
}

void read_data(TString input){

  std::ifstream infile((std::string) input);
  std::string iline;
  getline(infile,iline); //skip header

  while(getline(infile,iline)){
    std::string str;
    std::vector<double> val;
    stringstream ss(iline);
    while(getline(ss, str, ' ')){
      val.push_back(std::stod(str));    
    }
     delta.push_back(val[0]);
     x.push_back(val[1]);
     a.push_back(val[2]);    
     std::cout << val[0] << " " << val[1] << " " << val[2] << std::endl;
  }

}

