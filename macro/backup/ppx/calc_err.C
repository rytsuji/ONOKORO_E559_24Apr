#include <yaml-cpp/yaml.h>

int calc_err(std::string  reaction,std::string  target){

  double scale=1.0/8.0; //scale of accidental coincidence 
  double TotalBI=0.0;
  double TotalTime=0.0;
  int Nrun=0;

  double err_vdc_gr_mean=0;  
  double err_vdc_las_mean=0;
  double err_mhit_gr_mean=0;  
  double err_mhit_las_mean=0;
  double err_daq_mean=0;

  double rerr_vdc_gr_mean=0;  
  double rerr_vdc_las_mean=0;
  double rerr_mhit_gr_mean=0;  
  double rerr_mhit_las_mean=0;
  double rerr_daq_mean=0;
  
  double eff_vdc_gr_mean=0;  
  double eff_vdc_las_mean=0;
  double eff_mhit_gr_mean=0;  
  double eff_mhit_las_mean=0;
  double eff_daq_mean=0;
  
  double TotalBIScale;
  double BIScale;
  

  //read config
  std::ifstream file_config(Form("prm/spectrometer/gr/%s.yaml",reaction.c_str()));
  YAML::Node node  = YAML::Load(file_config);
  Double_t fMagneticField = node["magfield"].as<Double_t>();
  Double_t fMass = node["mass"].as<Double_t>();
  Int_t fAtomicNumber = node["atomicnum"].as<Int_t>();
  Double_t fRho = node["rho"].as<Double_t>();
  Double_t dE_gr=0;

  //target
  fstream target_info(Form("macro/ppx/target/%s.txt",target.c_str()));
  std::string line_target;
  getline(target_info,line_target);
  std::istringstream strs_target(line_target);
  std::string str_thick;
  std::string str_Aweight;
  strs_target  >> str_thick >> str_Aweight;
  Double_t thick=std::stod(str_thick);
  Double_t Aweight=std::stod(str_Aweight);
  
  //read runlist
  std::vector<std::string> run;
  ifstream runlist(Form("runlist/%s/runlist_%s.txt",reaction.c_str(),target.c_str()));
  std::string line_runlist;  
  while(getline(runlist,line_runlist)){
    run.push_back(line_runlist);
    //std::cout << "-----------run"  << run << "-----------" << std::endl; 
    /*
    */
  }

  BIScale=1.3260702*0.25*( ScaData(std::stoi(run[0]),28)+ScaData(std::stoi(run[0]),29)+ScaData(std::stoi(run[0]),30)+ScaData(std::stoi(run[0]),31) );

  const int n_file = run.size();
  TH1F* ht[n_file];
  TH1F* ha[n_file];
  
  for(int i=0;i<run.size();i++){
    std::cout << "***** processing run"  << run[i]  << " *****" <<std::endl;         

    Double_t eff=1.0;
    
    //Get GR VDC eff
    Double_t eff_vdc_gr=1.0;
    
    TFile *file_vdc_gr= TFile::Open(Form("output/hist_gr_eff/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_vdc_gr=(TDirectoryFile*)file_vdc_gr->Get("vdc_gr_eff");  
    TH1F *h_gr_x2 = (TH1F*)dir_vdc_gr->Get("eff_gr_x2");
    TH1F *h_gr_x1 = (TH1F*)dir_vdc_gr->Get("eff_gr_x1");
    TH1F *h_gr_u1 = (TH1F*)dir_vdc_gr->Get("eff_gr_u1");
    TH1F *h_gr_u2 = (TH1F*)dir_vdc_gr->Get("eff_gr_u2");
    
    Double_t acc_hit_gr[4]={(Double_t) h_gr_x1->GetBinContent(2),
			    (Double_t) h_gr_x2->GetBinContent(2),
			    (Double_t) h_gr_u1->GetBinContent(2),
			    (Double_t) h_gr_u2->GetBinContent(2)};

    Double_t req_hit_gr[4]={(Double_t) h_gr_x1->GetBinContent(1)+h_gr_x1->GetBinContent(2),
			    (Double_t) h_gr_x2->GetBinContent(1)+h_gr_x2->GetBinContent(2),
			    (Double_t) h_gr_u1->GetBinContent(1)+h_gr_u1->GetBinContent(2),
			    (Double_t) h_gr_u2->GetBinContent(1)+h_gr_u2->GetBinContent(2)};    

    Double_t eff_gr_x1 = acc_hit_gr[0]/req_hit_gr[0]; 
    Double_t err_eff_gr_x1 = eff_gr_x1*sqrt(acc_hit_gr[0]/pow(req_hit_gr[0],2.0)+req_hit_gr[0]/pow(acc_hit_gr[0],2.0));

    Double_t eff_gr_x2 = acc_hit_gr[1]/req_hit_gr[1]; 
    Double_t err_eff_gr_x2 = eff_gr_x2*sqrt(acc_hit_gr[1]/pow(req_hit_gr[1],2.0)+req_hit_gr[1]/pow(acc_hit_gr[1],2.0));
    
    Double_t eff_gr_u1 = acc_hit_gr[2]/req_hit_gr[2]; 
    Double_t err_eff_gr_u1 = eff_gr_u1*sqrt(acc_hit_gr[2]/pow(req_hit_gr[2],2.0)+req_hit_gr[2]/pow(acc_hit_gr[2],2.0));
    
    Double_t eff_gr_u2 = acc_hit_gr[3]/req_hit_gr[3]; 
    Double_t err_eff_gr_u2 = eff_gr_u2*sqrt(acc_hit_gr[3]/pow(req_hit_gr[3],2.0)+req_hit_gr[3]/pow(acc_hit_gr[3],2.0));


    eff_vdc_gr=eff_gr_x1*eff_gr_x2*eff_gr_u1*eff_gr_u2;
    double err_vdc_gr=sqrt(pow(err_eff_gr_x1*eff_gr_x2*eff_gr_u1*eff_gr_u2,2.0)+pow(eff_gr_x1*err_eff_gr_x2*eff_gr_u1*eff_gr_u2,2.0)+pow(eff_gr_x1*eff_gr_x2*err_eff_gr_u1*eff_gr_u2,2.0)+pow(eff_gr_x1*eff_gr_x2*eff_gr_u1*err_eff_gr_u2,2.0));
    
    std::cout << " eff  GR   VDC : " << eff_vdc_gr << " err : " << err_vdc_gr  << "" <<std::endl;
    
    //Get LAS VDC eff
    Double_t eff_vdc_las=1.0;
    TFile *file_vdc_las= TFile::Open(Form("output/hist_las_eff/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_vdc_las=(TDirectoryFile*)file_vdc_las->Get("vdc_las_eff");  
    TH1F *h_las_x1 = (TH1F*)dir_vdc_las->Get("eff_las_x1");
    TH1F *h_las_x2 = (TH1F*)dir_vdc_las->Get("eff_las_x2");
    TH1F *h_las_u1 = (TH1F*)dir_vdc_las->Get("eff_las_u1");
    TH1F *h_las_u2 = (TH1F*)dir_vdc_las->Get("eff_las_u2");
    TH1F *h_las_v1 = (TH1F*)dir_vdc_las->Get("eff_las_v1");
    TH1F *h_las_v2 = (TH1F*)dir_vdc_las->Get("eff_las_v2");

    Double_t acc_hit_las[6]={(Double_t) h_las_x1->GetBinContent(2),
			     (Double_t) h_las_x2->GetBinContent(2),
			     (Double_t) h_las_u1->GetBinContent(2),
			     (Double_t) h_las_u2->GetBinContent(2),
			     (Double_t) h_las_v1->GetBinContent(2),
			     (Double_t) h_las_v2->GetBinContent(2)};

    Double_t req_hit_las[6]={(Double_t) h_las_x1->GetBinContent(1)+h_las_x1->GetBinContent(2),
			     (Double_t) h_las_x2->GetBinContent(1)+h_las_x2->GetBinContent(2),
			     (Double_t) h_las_u1->GetBinContent(1)+h_las_u1->GetBinContent(2),
			     (Double_t) h_las_u2->GetBinContent(1)+h_las_u2->GetBinContent(2),
			     (Double_t) h_las_v1->GetBinContent(1)+h_las_v1->GetBinContent(2),
			     (Double_t) h_las_v2->GetBinContent(1)+h_las_v2->GetBinContent(2)};
    
    Double_t eff_las_x1= acc_hit_las[0]/req_hit_las[0];
    Double_t eff_las_x2= acc_hit_las[1]/req_hit_las[1];
    Double_t eff_las_u1= acc_hit_las[2]/req_hit_las[2];
    Double_t eff_las_u2= acc_hit_las[3]/req_hit_las[3];
    Double_t eff_las_v1= acc_hit_las[4]/req_hit_las[4];
    Double_t eff_las_v2= acc_hit_las[5]/req_hit_las[5];

    Double_t err_las_x1= acc_hit_las[0]/req_hit_las[0]*sqrt(acc_hit_las[0]/pow(req_hit_las[0],2.0)+req_hit_las[0]/pow(acc_hit_las[0],2.0));
    Double_t err_las_x2= acc_hit_las[1]/req_hit_las[1]*sqrt(acc_hit_las[1]/pow(req_hit_las[1],2.0)+req_hit_las[1]/pow(acc_hit_las[1],2.0));
    Double_t err_las_u1= acc_hit_las[2]/req_hit_las[2]*sqrt(acc_hit_las[2]/pow(req_hit_las[2],2.0)+req_hit_las[2]/pow(acc_hit_las[2],2.0));
    Double_t err_las_u2= acc_hit_las[3]/req_hit_las[3]*sqrt(acc_hit_las[3]/pow(req_hit_las[3],2.0)+req_hit_las[3]/pow(acc_hit_las[3],2.0));
    Double_t err_las_v1= acc_hit_las[4]/req_hit_las[4]*sqrt(acc_hit_las[4]/pow(req_hit_las[4],2.0)+req_hit_las[4]/pow(acc_hit_las[4],2.0));
    Double_t err_las_v2= acc_hit_las[5]/req_hit_las[5]*sqrt(acc_hit_las[5]/pow(req_hit_las[5],2.0)+req_hit_las[5]/pow(acc_hit_las[5],2.0));
      
    Double_t eff_las_xu=eff_las_x1*eff_las_x2*eff_las_u1*eff_las_u2;
    Double_t eff_las_xv=eff_las_x1*eff_las_x2*eff_las_v1*eff_las_v2;
    eff_vdc_las=eff_las_xu+(1-eff_las_xu)*eff_las_xv;

    Double_t product_eff_las=eff_las_x1*eff_las_x2*eff_las_u1*eff_las_u2*eff_las_v1*eff_las_v2;
    Double_t err_las_plane[6]={err_las_x1*(eff_las_x2*(eff_las_u1*eff_las_u2+eff_las_v1*eff_las_v2)-2*eff_las_x1*pow(eff_las_x2,2.0)*eff_las_u1*eff_las_u2*eff_las_v1*eff_las_v2),
			       err_las_x2*(eff_las_x1*(eff_las_u1*eff_las_u2+eff_las_v1*eff_las_v2)-2*eff_las_x2*pow(eff_las_x1,2.0)*eff_las_u1*eff_las_u2*eff_las_v1*eff_las_v2),
			       err_las_u1*(eff_las_u2*eff_las_x1*eff_las_x2-2*product_eff_las*product_eff_las/eff_las_u1),			       
			       err_las_u2*(eff_las_u1*eff_las_x1*eff_las_x2-2*product_eff_las*product_eff_las/eff_las_u2),			       
			       err_las_v1*(eff_las_v2*eff_las_x1*eff_las_x2-2*product_eff_las*product_eff_las/eff_las_v1),			       
			       err_las_v2*(eff_las_v1*eff_las_x1*eff_las_x2-2*product_eff_las*product_eff_las/eff_las_v2)};
    
    Double_t err_vdc_las=sqrt(pow(err_las_plane[0],2.0)+pow(err_las_plane[1],2.0)+pow(err_las_plane[2],2.0)+pow(err_las_plane[3],2.0)+pow(err_las_plane[4],2.0)+pow(err_las_plane[5],2.0));
    
    std::cout << "err las vdc pl_X1 " << err_las_x1 << std::endl;
    std::cout << " eff  LAS  VDC : " << eff_vdc_las << " err : " << err_vdc_las  <<std::endl;
    
    //Get GR & LAS mhit  eff
    Double_t eff_mhit_gr=1.0;
    TFile *file_mhit= TFile::Open(Form("output/calib/hist/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_mhit_gr=(TDirectoryFile*)file_mhit->Get("mhif_gr_eff");
    TH1F *h_mhit_gr = (TH1F*)dir_mhit_gr->Get("mhit_gr_cointrig");
    Double_t acc_mhit_gr= (Double_t) h_mhit_gr->GetBinContent(2);
    Double_t req_mhit_gr= (Double_t) h_mhit_gr->GetBinContent(1)+h_mhit_gr->GetBinContent(2);
    
    eff_mhit_gr = acc_mhit_gr/req_mhit_gr;
    Double_t err_mhit_gr = eff_mhit_gr*sqrt(acc_mhit_gr/pow(req_mhit_gr,2.0)+req_mhit_gr/pow(acc_mhit_gr,2.0));
    std::cout << " eff GR  mHit : " << eff_mhit_gr << " err: " <<  err_mhit_gr  << std::endl;
    
    Double_t eff_mhit_las=1.0;
    TDirectoryFile* dir_mhit_las=(TDirectoryFile*)file_mhit->Get("mhif_las_eff");  
    TH1F *h_mhit_las = (TH1F*)dir_mhit_las->Get("mhit_las_cointrig");
    Double_t acc_mhit_las= (Double_t) h_mhit_las->GetBinContent(2);
    Double_t req_mhit_las= (Double_t) h_mhit_las->GetBinContent(1)+h_mhit_las->GetBinContent(2);

    eff_mhit_las= acc_mhit_las/req_mhit_las;
    Double_t err_mhit_las = eff_mhit_gr*sqrt(acc_mhit_las/pow(req_mhit_las,2.0)+req_mhit_las/pow(acc_mhit_las,2.0));    
    std::cout << " eff LAS mHit : " << eff_mhit_las << " err: " << err_mhit_las << std::endl;
 
    //Get DAQ eff;
    Double_t eff_daq=1.0;
    Double_t dT = (Double_t) ScaData(std::stoi(run[i]),7)/10000.0;
    Double_t kg = (Double_t) ScaData(std::stoi(run[i]),6)/dT;
    Double_t kl = (Double_t) ScaData(std::stoi(run[i]),10)/dT;
    Double_t kc = (Double_t) ScaData(std::stoi(run[i]),15)/dT;
    Double_t mg = (Double_t) ScaData(std::stoi(run[i]),5)/dT;
    Double_t ml = (Double_t) ScaData(std::stoi(run[i]),17)/dT;
    Double_t GateWidth=1.0e-6; //10 (us)
    eff_daq= kl/ml;
    Double_t err_daq= eff_daq*sqrt(kl/(ml*ml)+ml/(kl*kl));
    std::cout << " eff DAQ : " << eff_daq << " err: " << err_daq << std::endl;
    std::cout << " Live/Trigger (count/s), eff DAQ"  << std::endl;
    std::cout << "   GR   : " << kg  << "/" << mg <<  " = " << kg/mg << std::endl;
    std::cout << "   LAS  : " << kl  << "/"  << ml << " = " << kl/ml << std::endl;
    
    
    int time=(int) dT;
    int hour = time/3600;
    time %= 3600;
    int min = time/60;
    time %= 60;
    int sec  = time;
    std::cout << "Time : " << hour << "h " << min << "min "<< sec << "sec" <<std::endl;
    TotalTime += dT;
    
    //Get BI(nC)
    Double_t BI=1.3260702*0.25*( ScaData(std::stoi(run[i]),28)+ScaData(std::stoi(run[i]),29)+ScaData(std::stoi(run[i]),30)+ScaData(std::stoi(run[i]),31) );
    TotalBI += BI;
    std::cout << "Beam Current (nA): " << BI/dT << std::endl;

    eff_vdc_gr_mean   += BI/BIScale*eff_vdc_gr;
    eff_vdc_las_mean  += BI/BIScale*eff_vdc_las;
    eff_mhit_gr_mean  += BI/BIScale*eff_mhit_gr;
    eff_mhit_las_mean += BI/BIScale*eff_mhit_las;
    eff_daq_mean += BI/BIScale*eff_daq;
    
    err_vdc_gr_mean   += pow(BI/BIScale,2.0)*err_vdc_gr;
    err_vdc_las_mean  += pow(BI/BIScale,2.0)*err_vdc_las;
    err_mhit_gr_mean  += pow(BI/BIScale,2.0)*err_mhit_gr;
    err_mhit_las_mean += pow(BI/BIScale,2.0)*err_mhit_las;
    err_daq_mean +=  pow(BI/BIScale,2.0)*err_daq;
    //reduced err
    rerr_vdc_gr_mean   += pow(BI/BIScale,2.0)*err_vdc_gr/eff_vdc_gr;  
    rerr_vdc_las_mean  += pow(BI/BIScale,2.0)*err_vdc_las/eff_vdc_las;  
    rerr_mhit_gr_mean  += pow(BI/BIScale,2.0)*err_mhit_gr/eff_mhit_gr;    
    rerr_mhit_las_mean += pow(BI/BIScale,2.0)*err_mhit_las/eff_mhit_las;    
    rerr_daq_mean +=  pow(BI/BIScale,2.0)*err_daq/eff_daq;  
    
    TotalBIScale += (BI/BIScale);
    
  }



  Double_t dOmega_gr=0.00;
  Double_t dOmega_las=0.00;

  if(reaction == "ppt"){
    dE_gr=153.0-145.0;
    dOmega_gr=0.00289662;
    dOmega_las=0.0112459;
  }else if(reaction=="pph"){
    dE_gr=153.0-145.0;
    dOmega_gr=0.00289662;
    dOmega_las=0.0112459;
  }else if(reaction=="pph_48Ca"){
    dE_gr=146.0-136.0;
    dOmega_gr=0.00292287;
    dOmega_las=0.0109863;
  }else{
    return 0;
  }
  

  
  Double_t targetTilted=1.0/cos(60.0*TMath::DegToRad());
  std::cout << "-----------------------" << std::endl;
  std::cout  << "  Beam Current (nA)  : " << TotalBI/TotalTime << std::endl;  
  std::cout  << "  Beam Charge  (nC)  : " << TotalBI << std::endl;
  std::cout  << "   target   (mg/cm2) : " << thick << std::endl;
  std::cout  << "   target   (g/mol)  : " << Aweight << std::endl;
  std::cout  << " target tilte factor : " << targetTilted << std::endl;  
  std::cout  << "     dE GR    (MeV)  : " << dE_gr << std::endl;
  std::cout  << "solid ang GR  (str)  : " << dOmega_gr << std::endl;
  std::cout  << "solid ang LAS (str)  : " << dOmega_las << std::endl;      


  std::cout << "" << std::endl;

  std::cout << "           " << " **mean eff** " << " **err** " << " **reduced err** " <<std::endl;
  std::cout << "GR VDC   : " << eff_vdc_gr_mean/TotalBIScale << " "  << err_vdc_gr_mean/TotalBIScale << " " << rerr_vdc_gr_mean/TotalBIScale << std::endl; 
  std::cout << "LAS VDC  : " << eff_vdc_las_mean/TotalBIScale << " "  << err_vdc_las_mean/TotalBIScale << " " << rerr_vdc_las_mean/TotalBIScale << std::endl;
  std::cout << "GR MHit  : " << eff_mhit_gr_mean/TotalBIScale << " "  << err_mhit_gr_mean/TotalBIScale << " " << rerr_mhit_gr_mean/TotalBIScale << std::endl;
  std::cout << "LAS MHit : " << eff_mhit_las_mean/TotalBIScale << " "  << err_mhit_las_mean/TotalBIScale << " " << rerr_mhit_las_mean/TotalBIScale << std::endl;
  std::cout << "DAQ eff  : " << eff_daq_mean/TotalBIScale << " "  << err_daq_mean/TotalBIScale << " " << rerr_daq_mean/TotalBIScale << std::endl;

  //Double_t err_TotalBI=sqrt(1.3260702*0.25*TotalBI+pow(TotalBI*0.0065/sqrt(12.0),2.0))/TotalBI;
  Double_t err_TotalBI=sqrt(1.3260702*0.25*TotalBI+pow(TotalBI*0.0065,2.0))/TotalBI;
  std::cout << "BI: " << TotalBI <<  " err: " << err_TotalBI <<std::endl;
  
  std::cout << "**** stat err (eff) **** " << sqrt ( (pow(rerr_vdc_gr_mean,2.0)+pow(rerr_vdc_las_mean,2.0)+pow(rerr_mhit_gr_mean,2.0)+pow(rerr_mhit_las_mean,2.0)+pow(rerr_daq_mean,2.0))/pow(TotalBIScale,2.0) + pow(err_TotalBI,2.0)) << std::endl;
  
  
  Double_t NA=6.0221407610e+23;
  Double_t eu=1.602176634e-19;

  //Double_t scale_tdx_ub=(1.0e+30)/((dOmega_gr*dOmega_las*dE_gr) * (TotalBI*(1.0e-9)/eu) * (targetTilted*thick*(1.0e-3)*NA/Aweight));

  //std::cout << scale_tdx_ub << std::endl;




  
  return 0;
}


