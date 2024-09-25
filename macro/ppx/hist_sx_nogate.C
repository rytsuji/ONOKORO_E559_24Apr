#include <yaml-cpp/yaml.h>

int hist_sx_nogate(std::string  reaction,std::string  target){

  double scale=1.0/8.0; //scale of accidental coincidence 
  double TotalBI=0.0;
  double TotalTime=0.0;
  //read config
  std::ifstream file_config(Form("prm/spectrometer/gr/%s.yaml",reaction.c_str()));
  YAML::Node node  = YAML::Load(file_config);
  Double_t fMagneticField = node["magfield"].as<Double_t>();
  Double_t fMass = node["mass"].as<Double_t>();
  Int_t fAtomicNumber = node["atomicnum"].as<Int_t>();
  Double_t fRho = node["rho"].as<Double_t>();
  Double_t dE_gr=7.0;//sqrt(fMass*fMass+pow(0.3*(Double_t) fAtomicNumber*fMagneticField*fRho*(1.0+0.0175),2.0))-sqrt(fMass*fMass+pow(0.3*(Double_t) fAtomicNumber*fMagneticField*fRho*(1.0-0.0175),2.0));

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


  const int n_file = run.size();
  TH1F* ht[n_file];
  TH1F* ha[n_file];
  
  for(int i=0;i<run.size();i++){
    std::cout << "***** processing run"  << run[i]  << " *****" <<std::endl;         

    Double_t eff=1.0;
    
    //hist phys
    TFile *file_phys= TFile::Open(Form("output/hist_phys_nogate/run%s.hist.root",run[i].c_str()));    
    TDirectoryFile* dir_phys=(TDirectoryFile*)file_phys->Get("phys");  
    ht[i] = (TH1F*)dir_phys->Get("sx");
    ha[i] = (TH1F*)dir_phys->Get("sx_ac");
    ht[i]->Sumw2();
    ha[i]->Sumw2();

    //Get GR VDC eff
    Double_t eff_vdc_gr=1.0;
    TFile *file_vdc_gr= TFile::Open(Form("output/hist_gr_eff/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_vdc_gr=(TDirectoryFile*)file_vdc_gr->Get("vdc_gr_eff");  
    TH1F *h_gr_x1 = (TH1F*)dir_vdc_gr->Get("eff_gr_x1");
    Double_t eff_gr_x1= (Double_t) h_gr_x1->GetBinContent(2)/(h_gr_x1->GetBinContent(1)+h_gr_x1->GetBinContent(2));
    TH1F *h_gr_x2 = (TH1F*)dir_vdc_gr->Get("eff_gr_x2");
    Double_t eff_gr_x2= (Double_t) h_gr_x2->GetBinContent(2)/(h_gr_x2->GetBinContent(1)+h_gr_x2->GetBinContent(2));    
    TH1F *h_gr_u1 = (TH1F*)dir_vdc_gr->Get("eff_gr_u1");
    Double_t eff_gr_u1= (Double_t) h_gr_u1->GetBinContent(2)/(h_gr_u1->GetBinContent(1)+h_gr_u1->GetBinContent(2));
    TH1F *h_gr_u2 = (TH1F*)dir_vdc_gr->Get("eff_gr_u2");
    Double_t eff_gr_u2= (Double_t) h_gr_u2->GetBinContent(2)/(h_gr_u2->GetBinContent(1)+h_gr_u2->GetBinContent(2));

    eff_vdc_gr=eff_gr_x1*eff_gr_x2*eff_gr_u1*eff_gr_u2;
    std::cout << " eff  GR   VDC : " << eff_vdc_gr << std::endl;
	
    //Get LAS VDC eff
    Double_t eff_vdc_las=1.0;
    TFile *file_vdc_las= TFile::Open(Form("output/hist_las_eff/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_vdc_las=(TDirectoryFile*)file_vdc_las->Get("vdc_las_eff");  
    TH1F *h_las_x1 = (TH1F*)dir_vdc_las->Get("eff_las_x1");
    Double_t eff_las_x1= (Double_t) h_las_x1->GetBinContent(2)/(h_las_x1->GetBinContent(1)+h_las_x1->GetBinContent(2));
    TH1F *h_las_x2 = (TH1F*)dir_vdc_las->Get("eff_las_x2");
    Double_t eff_las_x2= (Double_t) h_las_x2->GetBinContent(2)/(h_las_x2->GetBinContent(1)+h_las_x2->GetBinContent(2));    
    TH1F *h_las_u1 = (TH1F*)dir_vdc_las->Get("eff_las_u1");
    Double_t eff_las_u1= (Double_t) h_las_u1->GetBinContent(2)/(h_las_u1->GetBinContent(1)+h_las_u1->GetBinContent(2));
    TH1F *h_las_u2 = (TH1F*)dir_vdc_las->Get("eff_las_u2");
    Double_t eff_las_u2= (Double_t) h_las_u2->GetBinContent(2)/(h_las_u2->GetBinContent(1)+h_las_u2->GetBinContent(2));
    TH1F *h_las_v1 = (TH1F*)dir_vdc_las->Get("eff_las_v1");
    Double_t eff_las_v1= (Double_t) h_las_v1->GetBinContent(2)/(h_las_v1->GetBinContent(1)+h_las_v1->GetBinContent(2));
    TH1F *h_las_v2 = (TH1F*)dir_vdc_las->Get("eff_las_v2");
    Double_t eff_las_v2= (Double_t) h_las_v2->GetBinContent(2)/(h_las_v2->GetBinContent(1)+h_las_v2->GetBinContent(2));    

    Double_t eff_las_xu=eff_las_x1*eff_las_x2*eff_las_u1*eff_las_u2;
    Double_t eff_las_xv=eff_las_x1*eff_las_x2*eff_las_v1*eff_las_v2;
    eff_vdc_las=eff_las_xu+(1-eff_las_xu)*eff_las_xv;
    std::cout << " eff  LAS  VDC : " << eff_vdc_las << std::endl;
    
    //Get GR & LAS mhit  eff
    Double_t eff_mhit_gr=1.0;
    TFile *file_mhit= TFile::Open(Form("output/calib/hist/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_mhit_gr=(TDirectoryFile*)file_mhit->Get("mhif_gr_eff");
    TH1F *h_mhit_gr = (TH1F*)dir_mhit_gr->Get("mhit_gr_cointrig");
    eff_mhit_gr= (Double_t) h_mhit_gr->GetBinContent(2)/(h_mhit_gr->GetBinContent(1)+h_mhit_gr->GetBinContent(2));
    std::cout << " eff GR  mHit : " << eff_mhit_gr << std::endl;

    Double_t eff_mhit_las=1.0;
    TDirectoryFile* dir_mhit_las=(TDirectoryFile*)file_mhit->Get("mhif_las_eff");  
    TH1F *h_mhit_las = (TH1F*)dir_mhit_las->Get("mhit_las_cointrig");
    eff_mhit_las= (Double_t) h_mhit_las->GetBinContent(2)/(h_mhit_las->GetBinContent(1)+h_mhit_las->GetBinContent(2));
    std::cout << " eff LAS mHit : " << eff_mhit_las << std::endl;
 
    //Get DAQ eff;
    Double_t eff_daq=1.0;
    Double_t dT = (Double_t) ScaData(std::stoi(run[i]),7)/10000.0;
    Double_t kg = (Double_t) ScaData(std::stoi(run[i]),6)/dT;
    Double_t kl = (Double_t) ScaData(std::stoi(run[i]),10)/dT;
    Double_t kc = (Double_t) ScaData(std::stoi(run[i]),15)/dT;
    Double_t mg = (Double_t) ScaData(std::stoi(run[i]),5)/dT;
    Double_t ml = (Double_t) ScaData(std::stoi(run[i]),17)/dT;
    Double_t GateWidth=1.0e-6; //10 (us)
    //solve quadratic equation for obtaing mc
    Double_t b_mc=mg+ml-(kl-kg)/(GateWidth*kg);
    Double_t c_mc=mg*ml-( (kl+kc)*mg - (kg+kc)*ml)/(GateWidth*kg);    
    //Double_t mc=(-b_mc-sqrt(pow(b_mc,2.0)-4*c_mc))/2;
    Double_t mc=-((kl+kc)*mg-(kg+kc)*ml)/(kl-kg);
    //eff_daq=kc/mc;
    eff_daq=(kg/mg)*(kl/ml);

    std::cout << "  Live/Trigger (count/s), eff DAQ"  << std::endl;
    std::cout << " GR   : " << kg  << "  " << mg <<  "  " << kg/mg << std::endl;
    std::cout << " LAS  : " << kl  << "  "  << ml << "  " << kl/ml << std::endl;
    std::cout << " Coin : " << kc  << "  "  << mc << "  " << eff_daq << std::endl;    
    /*
    std::cout << " eff  GR  trig: " << kg/mg << std::endl;      
    std::cout << " eff  LAS trig: " << kl/ml  << std::endl;      
    std::cout << " eff Coin trig: " << eff_daq << std::endl;      
    */
    int time=(int) dT;
    int hour = time/3600;
    time %= 3600;
    int min = time/60;
    time %= 60;
    int sec  = time;
    std::cout << " Time : " << hour << "h " << min << "min "<< sec << "sec" <<std::endl;
    TotalTime += dT;
    
    //Get BI(nC)
    Double_t BI=1.3260702*0.25*( ScaData(std::stoi(run[i]),28)+ScaData(std::stoi(run[i]),29)+ScaData(std::stoi(run[i]),30)+ScaData(std::stoi(run[i]),31) );
    TotalBI += BI;
    std::cout << "Beam Current (nA): " << BI/dT << std::endl;
    //scale histograms
    eff=eff_mhit_las*eff_mhit_gr*eff_vdc_gr*eff_vdc_las*eff_daq;
    ht[i]->Scale(1.0/eff);    
    ha[i]->Scale(scale/eff);    
  }


  Double_t dOmega_gr=0.00191504;
  Double_t dOmega_las=0.0112459;
  /*
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
  */

  
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

  Double_t NA=6.0221407610e+23;
  Double_t eu=1.602176634e-19;

  //Double_t scale_tdx_ub=(10e+30)/((dOmega_gr*dOmega_las*dE_gr) * (TotalBI*(1.0e-9)/eu) * (targetTilted*thick*(1.0e-3)*NA/Aweight));
  Double_t scale_integrated_tdx=(10e+30)/((TotalBI*(1.0e-9)/eu) * (targetTilted*thick*(1.0e-3)*NA/Aweight));

  std::cout << scale_integrated_tdx << std::endl;
  
  int nBin=ht[0]->GetXaxis()->GetNbins();
  int xMin=ht[0]->GetXaxis()->GetXmin();
  int xMax=ht[0]->GetXaxis()->GetXmax();

  TH1F *sx_tc=new TH1F("sx_tc", "true coin",nBin,xMin,xMax);
  TH1F *sx_ac=new TH1F("sx_ac", "accidental coin",nBin,xMin,xMax);
  sx_tc->Sumw2();
  sx_ac->Sumw2();
  for(int i=0;i<n_file;i++){
    sx_tc->Add(ht[i],1.0);
    sx_ac->Add(ha[i],1.0);
  }
  sx_tc->Scale(scale_integrated_tdx);
sx_ac->Scale(scale_integrated_tdx);


  TH1F *sx=new TH1F("sx", "sx",nBin,xMin,xMax);
  sx->Sumw2();
  sx->Add(sx_tc,1.0);
  sx->Add(sx_ac,-1.0);
  
  TH1F *sx0=new TH1F("sx0", "sx0",nBin,xMin,xMax);
  sx0->Add(sx,1.0);
  sx0->Sumw2(0);

  //sx->GetXaxis()->ZoomOut(0.6,0.5);
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht sx E1");
  sx0->Draw("same");
  
  sx_tc->Sumw2(0);
  sx_ac->Sumw2(0);
  sx_ac->SetLineColor(2);


  //TFile *fout = new TFile(Form("macro/ppx/output_sx/%s_%s_momentum.root",reaction.c_str(),target.c_str()),"RECREATE");
  TFile *fout = new TFile(Form("output/ppx/%s_%s.nogate.root",reaction.c_str(),target.c_str()),"RECREATE");
  //fout->mkdir("phys"); 
  //phys->cd();
  fout->Add(sx);
  fout->Add(sx0);

  sx->Write();
  sx0->Write();
  sx_tc->Write();
  sx_ac->Write();  

  //fout->Close();
  return 0;
}


