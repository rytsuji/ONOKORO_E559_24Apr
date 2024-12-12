const int nFile=1;

std::vector<std::vector<double>> x_gr;
std::vector<std::vector<double>> x_las;
std::vector<std::vector<double>> T_gr;
std::vector<std::vector<double>> T_las;
std::vector<std::vector<double>> sp;
std::vector<double> Brho_gr;
std::vector<double> Brho_las;
const double mp=938.78;
const double mt=2808.92;

const int nPrm=7;

void chi2(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
void read_data();

int Li_ppt(){

  read_data();
  std::cout << "hoge" << std::endl;
  T_gr.resize(nFile);
  T_las.resize(nFile);
  sp.resize(nFile);
  
  TMinuit *min = new TMinuit(nPrm);// set number of parameters
  min->SetPrintLevel(1);
  int ierflg = 0;
  
  //Intialize of parameters
  double vstart[nPrm];
  for(int i=0;i<nPrm;i++){
    vstart[i] = 0.0;
  }
  
  vstart[0]=226.0; //Beam energy
  vstart[1]=0.0; //x offset gr
  //vstart[2]=-4.5916025e-05; //1/D gr
  vstart[2]=-4.1186797e-05; //1/D gr
  vstart[3]=0.0; //x offset las
  //vstart[4]=0.000218152; //1/D las
  vstart[4]=0.00019201499; //1/D las

  vstart[5]=0.0;
  vstart[6]=0.0;  
  
  
  //step width
  double step[nPrm];
  for(int i=0;i<nPrm;i++){
      step[i]=1.0e-15;
  }
  step[0]=0.01;
  step[1]=0.01;
  step[2]=1.0e-9;  
  step[3]=0.01;
  step[4]=1.0e-8;    

  
  //set limit of prm
  for(int i=0;i<nPrm;i++){
    min->mnparm(i, Form("p%d",i), vstart[i], step[i], 0, 0, ierflg);
  }

  min->mnparm(0, Form("p%d",0), vstart[0], step[0], 225.5, 226.5, ierflg);
  min->mnparm(1, Form("p%d",1), vstart[1], step[1], -20, 20, ierflg);
  min->mnparm(2, Form("p%d",2), vstart[2], step[2], vstart[2]*0.99, vstart[2]*1.01, ierflg);
  min->mnparm(3, Form("p%d",3), vstart[3], step[3], -10, 10, ierflg);    
  min->mnparm(4, Form("p%d",4), vstart[4], step[4], vstart[4]*0.95, vstart[4]*1.05, ierflg);    
  min->SetFCN(chi2);
  //min->FixParameter(0);
  //min->FixParameter(1);    
  min->FixParameter(2);
  min->FixParameter(4);  
  min->FixParameter(5);
  min->FixParameter(6);
  int migrad_stats = min->Migrad();
  //migrad_stats = min->Migrad(); 
  
  //TString oname="work/ang_gr/dat/gr_a.yaml"; 
  //ofstream ofile((std::string) oname);
  
  double par[nPrm]; 
  double par_err[nPrm];
  
  cout<<"**************************************"<<endl;
  for(int i=0;i<nPrm;i++){
    min->GetParameter(i,par[i],par_err[i]);
    cout<<"p" << i << ": "<< par[i] <<" +/- "<< par_err[i] <<endl;
  }
  
  
  TTree *tree = new TTree("tree","tree");
  tree->Branch("x_gr",&x_gr);
  tree->Branch("x_las",&x_las);  
  tree->Branch("T_gr",&T_gr);
  tree->Branch("T_las",&T_las);  
  tree->Branch("sp",&sp);
  
  
  for(int i=0; i<nFile; i++){
    for(int j=0; j<x_gr[i].size(); j++){
      double val=-1000;
      double p_gr=0.3*Brho_gr[i]*(1+ ((par[1]+x_gr[i][j])*par[2]+par[5]*pow(x_gr[i][j],2.0)));
      double p_las=0.3*Brho_las[i]*(1+ ((par[3]+x_las[i][j])*par[4]+par[6]*pow(x_las[i][j],2.0)));      

      val=par[0]-(sqrt(p_gr*p_gr+mp*mp)-mp)-(sqrt(p_las*p_las+mt*mt)-mt);
      T_gr[i].push_back(sqrt(p_gr*p_gr+mp*mp)-mp);
      T_las[i].push_back(sqrt(p_las*p_las+mt*mt)-mt);      
      sp[i].push_back(val);
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
    for(int j=0; j<x_gr[i].size(); j++){
      
      double val=-1000;

      double p_gr=0.3*Brho_gr[i]*(1+ ((par[1]+x_gr[i][j])*par[2]+par[5]*pow(x_gr[i][j],2.0)));
      double p_las=0.3*Brho_las[i]*(1+ ((par[3]+x_las[i][j])*par[4]+par[6]*pow(x_las[i][j],2.0)));      
     
      val=par[0]-(sqrt(p_gr*p_gr+mp*mp)-mp)-(sqrt(p_las*p_las+mt*mt)-mt);
      chisq += pow(val-2.468,2.0);
    }
  }
  
  f = chisq;
  
}


void read_data(){
  x_gr.resize(nFile);
  x_las.resize(nFile);        

  //delta93.5-107%

  double RhoGR=3.0;
  double RhoLAS=1.75;

  
  //Brho_gr.push_back(609.943*RhoGR);
  //Brho_las.push_back(1232.124*RhoLAS);
  //Brho_gr.push_back(609.975*RhoGR);
  //Brho_las.push_back(1232.104*RhoLAS);

		     
  Brho_gr.push_back(635.358*RhoGR);  
  Brho_las.push_back(1071.412*RhoLAS);
  //Brho_gr.push_back(635.358*RhoGR);  
  //Brho_las.push_back(1071.414*RhoLAS);

  //Brho_gr.push_back(660.772*RhoGR);
  //Brho_las.push_back(910.7011*RhoLAS);
  //Brho_gr.push_back(660.791*RhoGR);
  //Brho_las.push_back(910.733*RhoLAS);
 
  
  std::string dir="work/Li_ppt/dat/";
  //std::string file[nFile]={"ppt_kfn.dat","ppt_kf0.dat","ppt_kfp.dat"};
  std::string file[nFile]={"ppt_kf0.dat"};

  
   
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
      x_gr[iFile].push_back(Val[0]);
      x_las[iFile].push_back(Val[1]);
    }    
  }
}
  
