

#include <yaml-cpp/yaml.h>
void hist_momentum(std::string  reaction,std::string  target){

  double scale=1.0/8.0; //scale of accidental coincidence 
  double BI=0;

  //read config
  std::ifstream file_config(Form("prm/spectrometer/gr/%s.yaml",reaction.c_str()));
  YAML::Node node  = YAML::Load(file_config);
  Double_t fMagneticField = node["magfield"].as<Double_t>();
  Double_t fMass = node["mass"].as<Double_t>();
  Int_t fAtomicNumber = node["atomicnum"].as<Int_t>();
  Double_t fRho = node["rho"].as<Double_t>();
  Double_t dE_gr=1.5;

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
  TH2F* ht_px[n_file];
  TH2F* ha_px[n_file];

  TH2F* ht_py[n_file];
  TH2F* ha_py[n_file];

  TH2F* ht_pz[n_file];
  TH2F* ha_pz[n_file];

  TH2F* ht_p[n_file];
  TH2F* ha_p[n_file];
  
  TH2F* ht_gr[n_file];
  TH2F* ha_gr[n_file];
  
  for(int i=0;i<run.size();i++){
    std::cout << "processing run"  << run[i]  << std::endl;         

    Double_t eff=1.0;
    
    //hist phys
    TFile *file_phys= TFile::Open(Form("output/hist_phys_carbon/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_phys=(TDirectoryFile*)file_phys->Get("phys");  
    ht_px[i] = (TH2F*)dir_phys->Get("px_sx_tc");
    ha_px[i] = (TH2F*)dir_phys->Get("px_sx_ac");

    ht_py[i] = (TH2F*)dir_phys->Get("py_sx_tc");
    ha_py[i] = (TH2F*)dir_phys->Get("py_sx_ac");

    ht_pz[i] = (TH2F*)dir_phys->Get("pz_sx_tc");
    ha_pz[i] = (TH2F*)dir_phys->Get("pz_sx_ac");

    ht_p[i] = (TH2F*)dir_phys->Get("p_sx_tc");
    ha_p[i] = (TH2F*)dir_phys->Get("p_sx_ac");

    ht_gr[i] = (TH2F*)dir_phys->Get("tke_gr_sx_tc");
    ha_gr[i] = (TH2F*)dir_phys->Get("tke_gr_sx_ac");


    
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

    //Get BI(nC)
    BI += 1.3260702*0.25*( ScaData(std::stoi(run[i]),28)+ScaData(std::stoi(run[i]),29)+ScaData(std::stoi(run[i]),30)+ScaData(std::stoi(run[i]),31) );
    
    //scale histograms
    eff=eff_mhit_las*eff_mhit_gr*eff_vdc_gr*eff_vdc_las*eff_daq;

    ht_px[i]->Scale(1.0/eff);    
    ha_px[i]->Scale(scale/eff);

    ht_py[i]->Scale(1.0/eff);    
    ha_py[i]->Scale(scale/eff);    

    ht_pz[i]->Scale(1.0/eff);    
    ha_pz[i]->Scale(scale/eff);

    ht_p[i]->Scale(1.0/eff);    
    ha_p[i]->Scale(scale/eff);

    ht_gr[i]->Scale(1.0/eff);    
    ha_gr[i]->Scale(scale/eff);    
 
  }


  Double_t dOmega_gr=0.00191504; //str
  //Double_t dOmega_gr=0.0018; //str
  Double_t dOmega_las=0.0112459; //str
  //Double_t dOmega_las=0.0119; //str
  Double_t targetTilted=1.0/cos(60.0*TMath::DegToRad());
  std::cout << "-----------------------" << std::endl;
  std::cout  << "      BI      (nC)   : " << BI << std::endl;
  std::cout  << "   target   (mg/cm2) : " << thick << std::endl;
  std::cout  << "   target   (g/mol)  : " << Aweight << std::endl;
  std::cout  << " target tilte factor : " << targetTilted << std::endl;  
  std::cout  << "     dE GR    (MeV)  : " << dE_gr << std::endl;
  std::cout  << "solid ang GR  (str)  : " << dOmega_gr << std::endl;
  std::cout  << "solid ang LAS (str)  : " << dOmega_las << std::endl;      

  Double_t NA=6.0221407610e+23;
  Double_t eu=1.602176634e-19;

  Double_t scale_tdx_ub=(10e+30)/((dOmega_gr*dOmega_las*dE_gr) * (BI*(1.0e-9)/eu) * (targetTilted*thick*(1.0e-3)*NA/Aweight));

  std::cout << scale_tdx_ub << std::endl;
  
  int xNBin_px=ht_px[0]->GetXaxis()->GetNbins();
  int xMin_px=ht_px[0]->GetXaxis()->GetXmin();
  int xMax_px=ht_px[0]->GetXaxis()->GetXmax();
  int yNBin_px=ht_px[0]->GetYaxis()->GetNbins();
  int yMin_px=ht_px[0]->GetYaxis()->GetXmin();
  int yMax_px=ht_px[0]->GetYaxis()->GetXmax();


  int xNBin_py=ht_py[0]->GetXaxis()->GetNbins();
  int xMin_py=ht_py[0]->GetXaxis()->GetXmin();
  int xMax_py=ht_py[0]->GetXaxis()->GetXmax();
  int yNBin_py=ht_py[0]->GetYaxis()->GetNbins();
  int yMin_py=ht_py[0]->GetYaxis()->GetXmin();
  int yMax_py=ht_py[0]->GetYaxis()->GetXmax();

  int xNBin_pz=ht_pz[0]->GetXaxis()->GetNbins();
  int xMin_pz=ht_pz[0]->GetXaxis()->GetXmin();
  int xMax_pz=ht_pz[0]->GetXaxis()->GetXmax();
  int yNBin_pz=ht_pz[0]->GetYaxis()->GetNbins();
  int yMin_pz=ht_pz[0]->GetYaxis()->GetXmin();
  int yMax_pz=ht_pz[0]->GetYaxis()->GetXmax();

  int xNBin_p=ht_p[0]->GetXaxis()->GetNbins();
  int xMin_p=ht_p[0]->GetXaxis()->GetXmin();
  int xMax_p=ht_p[0]->GetXaxis()->GetXmax();
  int yNBin_p=ht_p[0]->GetYaxis()->GetNbins();
  int yMin_p=ht_p[0]->GetYaxis()->GetXmin();
  int yMax_p=ht_p[0]->GetYaxis()->GetXmax();

  int xNBin_gr=ht_gr[0]->GetXaxis()->GetNbins();
  int xMin_gr=ht_gr[0]->GetXaxis()->GetXmin();
  int xMax_gr=ht_gr[0]->GetXaxis()->GetXmax();
  int yNBin_gr=ht_gr[0]->GetYaxis()->GetNbins();
  int yMin_gr=ht_gr[0]->GetYaxis()->GetXmin();
  int yMax_gr=ht_gr[0]->GetYaxis()->GetXmax();

  TH2F *px_tc=new TH2F("px_tc", "true coin",xNBin_px,xMin_px,xMax_px,yNBin_px,yMin_px,yMax_px);
  TH2F *px_ac=new TH2F("px_ac", "acc coin",xNBin_px,xMin_px,xMax_px,yNBin_px,yMin_px,yMax_px);  
  px_tc->Sumw2();
  px_ac->Sumw2();

  TH2F *py_tc=new TH2F("py_tc", "true coin",xNBin_py,xMin_py,xMax_py,yNBin_py,yMin_py,yMax_py);
  TH2F *py_ac=new TH2F("py_ac", "acc coin",xNBin_py,xMin_py,xMax_py,yNBin_py,yMin_py,yMax_py);  
  py_tc->Sumw2();
  py_ac->Sumw2();

  TH2F *pz_tc=new TH2F("pz_tc", "true coin",xNBin_pz,xMin_pz,xMax_pz,yNBin_pz,yMin_pz,yMax_pz);
  TH2F *pz_ac=new TH2F("pz_ac", "acc coin",xNBin_pz,xMin_pz,xMax_pz,yNBin_pz,yMin_pz,yMax_pz);  
  pz_tc->Sumw2();
  pz_ac->Sumw2();

  TH2F *p_tc=new TH2F("p_tc", "true coin",xNBin_p,xMin_p,xMax_p,yNBin_p,yMin_p,yMax_p);
  TH2F *p_ac=new TH2F("p_ac", "acc coin",xNBin_p,xMin_p,xMax_p,yNBin_p,yMin_p,yMax_p);  
  p_tc->Sumw2();
  p_ac->Sumw2();


  TH2F *gr_tc=new TH2F("gr_tc", "true coin",xNBin_gr,xMin_gr,xMax_gr,yNBin_gr,yMin_gr,yMax_gr);
  TH2F *gr_ac=new TH2F("gr_ac", "acc coin",xNBin_gr,xMin_gr,xMax_gr,yNBin_gr,yMin_gr,yMax_gr);  
  gr_tc->Sumw2();
  gr_ac->Sumw2();
  
  for(int i=0;i<n_file;i++){
    
    px_tc->Add(ht_px[i],1.0);
    px_ac->Add(ha_px[i],1.0);

    py_tc->Add(ht_py[i],1.0);
    py_ac->Add(ha_py[i],1.0);
    
    pz_tc->Add(ht_pz[i],1.0);
    pz_ac->Add(ha_pz[i],1.0);

    p_tc->Add(ht_p[i],1.0);
    p_ac->Add(ha_p[i],1.0);

    gr_tc->Add(ht_gr[i],1.0);
    gr_ac->Add(ha_gr[i],1.0);
    
  }

  px_tc->Scale(scale_tdx_ub);
  px_ac->Scale(scale_tdx_ub);

  py_tc->Scale(scale_tdx_ub);
  py_ac->Scale(scale_tdx_ub);

  pz_tc->Scale(scale_tdx_ub);
  pz_ac->Scale(scale_tdx_ub);

  p_tc->Scale(scale_tdx_ub);
  p_ac->Scale(scale_tdx_ub);

  gr_tc->Scale(scale_tdx_ub);
  gr_ac->Scale(scale_tdx_ub);


  
  TFile *fout = new TFile(Form("output/ppx/momentum/%s_%s.2d.root",reaction.c_str(),target.c_str()),"RECREATE");

  fout->Add(px_tc);
  fout->Add(px_ac);

  fout->Add(py_tc);
  fout->Add(py_ac);

  fout->Add(pz_tc);
  fout->Add(pz_ac);

  fout->Add(p_tc);
  fout->Add(p_ac);

  fout->Add(gr_tc);
  fout->Add(gr_ac);

  px_tc->Write();
  px_ac->Write();

  py_tc->Write();
  py_ac->Write();

  pz_tc->Write();
  pz_ac->Write();

  p_tc->Write();
  p_ac->Write();

  gr_tc->Write();
  gr_ac->Write();
  
  //fout->Close();

}


