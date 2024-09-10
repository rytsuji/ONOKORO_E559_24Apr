

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
  Double_t dE_gr=sqrt(fMass*fMass+pow(0.3*(Double_t) fAtomicNumber*fMagneticField*fRho*(1.0+0.0175),2.0))-sqrt(fMass*fMass+pow(0.3*(Double_t) fAtomicNumber*fMagneticField*fRho*(1.0-0.0175),2.0));

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
  TH1F* ht_perp[n_file];
  TH1F* ha_perp[n_file];

  TH1F* ht_para[n_file];
  TH1F* ha_para[n_file];

  TH1F* ht_tot[n_file];
  TH1F* ha_tot[n_file];

  TH1F* ht_gr[n_file];
  TH1F* ha_gr[n_file];

  TH1F* ht_las[n_file];
  TH1F* ha_las[n_file];
  
  for(int i=0;i<run.size();i++){
    std::cout << "processing run"  << run[i]  << std::endl;         

    Double_t eff=1.0;
    
    //hist phys
    TFile *file_phys= TFile::Open(Form("output/hist_phys/run%s.hist.root",run[i].c_str()));
    TDirectoryFile* dir_phys=(TDirectoryFile*)file_phys->Get("phys");  
    ht_perp[i] = (TH1F*)dir_phys->Get("p_perp_tc");
    ha_perp[i] = (TH1F*)dir_phys->Get("p_perp_ac");
    ht_perp[i]->Sumw2();
    ha_perp[i]->Sumw2();
    
    ht_para[i] = (TH1F*)dir_phys->Get("p_para_tc");
    ha_para[i] = (TH1F*)dir_phys->Get("p_para_ac");
    ht_para[i]->Sumw2();
    ha_para[i]->Sumw2();
    
    ht_tot[i] = (TH1F*)dir_phys->Get("p_tot_tc");
    ha_tot[i] = (TH1F*)dir_phys->Get("p_tot_ac");
    ht_tot[i]->Sumw2();
    ha_tot[i]->Sumw2();

    ht_gr[i] = (TH1F*)dir_phys->Get("tke_gr");
    ha_gr[i] = (TH1F*)dir_phys->Get("tke_gr_ac");
    ht_gr[i]->Sumw2();
    ha_gr[i]->Sumw2();

    ht_las[i] = (TH1F*)dir_phys->Get("tke_las");
    ha_las[i] = (TH1F*)dir_phys->Get("tke_las_ac");
    ht_las[i]->Sumw2();
    ha_las[i]->Sumw2();


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

    ht_perp[i]->Scale(1.0/eff);    
    ha_perp[i]->Scale(scale/eff);    

    ht_para[i]->Scale(1.0/eff);    
    ha_para[i]->Scale(scale/eff);    

    ht_tot[i]->Scale(1.0/eff);    
    ha_tot[i]->Scale(scale/eff);

    ht_gr[i]->Scale(1.0/eff);    
    ha_gr[i]->Scale(scale/eff);

    ht_las[i]->Scale(1.0/eff);    
    ha_las[i]->Scale(scale/eff);    
  }


  Double_t dOmega_gr=0.0056; //str
  //Double_t dOmega_gr=0.0018; //str
  Double_t dOmega_las=0.012; //str
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
  
  int nBin_perp=ht_perp[0]->GetXaxis()->GetNbins();
  int xMin_perp=ht_perp[0]->GetXaxis()->GetXmin();
  int xMax_perp=ht_perp[0]->GetXaxis()->GetXmax();

  int nBin_para=ht_para[0]->GetXaxis()->GetNbins();
  int xMin_para=ht_para[0]->GetXaxis()->GetXmin();
  int xMax_para=ht_para[0]->GetXaxis()->GetXmax();

  int nBin_tot=ht_tot[0]->GetXaxis()->GetNbins();
  int xMin_tot=ht_tot[0]->GetXaxis()->GetXmin();
  int xMax_tot=ht_tot[0]->GetXaxis()->GetXmax();

  int nBin_gr=ht_gr[0]->GetXaxis()->GetNbins();
  int xMin_gr=ht_gr[0]->GetXaxis()->GetXmin();
  int xMax_gr=ht_gr[0]->GetXaxis()->GetXmax();


  int nBin_las=ht_las[0]->GetXaxis()->GetNbins();
  int xMin_las=ht_las[0]->GetXaxis()->GetXmin();
  int xMax_las=ht_las[0]->GetXaxis()->GetXmax();


  TH1F *p_perp_tc=new TH1F("p_perp_tc", "true coin",nBin_perp,xMin_perp,xMax_perp);
  TH1F *p_perp_ac=new TH1F("p_perp_ac", "acc coin",nBin_perp,xMin_perp,xMax_perp);
  
  TH1F *p_para_tc=new TH1F("p_para_tc", "true coin",nBin_para,xMin_para,xMax_para);
  TH1F *p_para_ac=new TH1F("p_para_ac", "acc coin",nBin_para,xMin_para,xMax_para);
  
  TH1F *p_tot_tc=new TH1F("p_tot_tc", "true coin",nBin_tot,xMin_tot,xMax_tot);
  TH1F *p_tot_ac=new TH1F("p_tot_ac", "acc coin",nBin_tot,xMin_tot,xMax_tot);

  TH1F *tke_gr_tc=new TH1F("tke_gr_tc", "true coin",nBin_gr,xMin_gr,xMax_gr);
  TH1F *tke_gr_ac=new TH1F("tke_gr_ac", "acc coin",nBin_gr,xMin_gr,xMax_gr);

  TH1F *tke_las_tc=new TH1F("tke_las_tc", "true coin",nBin_las,xMin_las,xMax_las);
  TH1F *tke_las_ac=new TH1F("tke_las_ac", "acc coin",nBin_las,xMin_las,xMax_las);    



  p_perp_tc->Sumw2();
  p_perp_ac->Sumw2();

  p_para_tc->Sumw2();
  p_para_ac->Sumw2();

  p_tot_tc->Sumw2();
  p_tot_ac->Sumw2();

  tke_gr_tc->Sumw2();
  tke_gr_ac->Sumw2();

  tke_las_tc->Sumw2();
  tke_las_ac->Sumw2();  
  
  for(int i=0;i<n_file;i++){
    p_perp_tc->Add(ht_perp[i],1.0);
    p_perp_ac->Add(ha_perp[i],1.0);

    p_para_tc->Add(ht_para[i],1.0);
    p_para_ac->Add(ha_para[i],1.0);

    p_tot_tc->Add(ht_tot[i],1.0);
    p_tot_ac->Add(ha_tot[i],1.0);


    tke_gr_tc->Add(ht_gr[i],1.0);
    tke_gr_ac->Add(ha_gr[i],1.0);
    
    tke_las_tc->Add(ht_las[i],1.0);
    tke_las_ac->Add(ha_las[i],1.0);

    
  }

  p_perp_tc->Scale(scale_tdx_ub);
  p_perp_ac->Scale(scale_tdx_ub);

  p_para_tc->Scale(scale_tdx_ub);
  p_para_ac->Scale(scale_tdx_ub);

  p_tot_tc->Scale(scale_tdx_ub);
  p_tot_ac->Scale(scale_tdx_ub);


  tke_gr_tc->Scale(scale_tdx_ub);
  tke_gr_ac->Scale(scale_tdx_ub);

  tke_las_tc->Scale(scale_tdx_ub);
  tke_las_ac->Scale(scale_tdx_ub);  
  
  TH1F *p_perp=new TH1F("p_perp", "p_perp",nBin_perp,xMin_perp,xMax_perp);
  p_perp->Sumw2();
  p_perp->Add(p_perp_tc,1.0);
  p_perp->Add(p_perp_ac,-1.0);
  
  TH1F *p_perp0=new TH1F("p_perp0", "p_perp0",nBin_perp,xMin_perp,xMax_perp);
  p_perp0->Add(p_perp,1.0);
  p_perp0->Sumw2(0);


  TH1F *p_para=new TH1F("p_para", "p_para",nBin_para,xMin_para,xMax_para);
  p_para->Sumw2();
  p_para->Add(p_para_tc,1.0);
  p_para->Add(p_para_ac,-1.0);
  
  TH1F *p_para0=new TH1F("p_para0", "p_para0",nBin_para,xMin_para,xMax_para);
  p_para0->Add(p_para,1.0);
  p_para0->Sumw2(0);


  TH1F *p_tot=new TH1F("p_tot", "p_tot",nBin_tot,xMin_tot,xMax_tot);
  p_tot->Sumw2();
  p_tot->Add(p_tot_tc,1.0);
  p_tot->Add(p_tot_ac,-1.0);
  
  TH1F *p_tot0=new TH1F("p_tot0", "p_tot0",nBin_tot,xMin_tot,xMax_tot);
  p_tot0->Add(p_tot,1.0);
  p_tot0->Sumw2(0);


  TH1F *tke_gr=new TH1F("tke_gr", "tke_gr",nBin_gr,xMin_gr,xMax_gr);
  tke_gr->Sumw2();
  tke_gr->Add(tke_gr_tc,1.0);
  tke_gr->Add(tke_gr_ac,-1.0);

  TH1F *tke_gr0=new TH1F("tke_gr0", "tke_gr0",nBin_gr,xMin_gr,xMax_gr);
  tke_gr0->Add(tke_gr,1.0);
  tke_gr0->Sumw2(0);


  TH1F *tke_las=new TH1F("tke_las", "tke_las",nBin_las,xMin_las,xMax_las);
  tke_las->Sumw2();
  tke_las->Add(tke_las_tc,1.0);
  tke_las->Add(tke_las_ac,-1.0);

  TH1F *tke_las0=new TH1F("tke_las0", "tke_las",nBin_las,xMin_las,xMax_las);
  tke_las0->Add(tke_las,1.0);
  tke_las0->Sumw2(0);  

  


  
  p_perp_tc->Sumw2(0);
  p_perp_ac->Sumw2(0);
  p_perp_ac->SetLineColor(2);

  p_para_tc->Sumw2(0);
  p_para_ac->Sumw2(0);
  p_para_ac->SetLineColor(2);

  p_tot_tc->Sumw2(0);
  p_tot_ac->Sumw2(0);
  p_tot_ac->SetLineColor(2);

  Int_t rebin=4;
  
  p_perp->Rebin(rebin);
  p_perp0->Rebin(rebin);
  p_perp_tc->Rebin(rebin);
  p_perp_ac->Rebin(rebin);  

  p_para->Rebin(rebin);
  p_para0->Rebin(rebin);
  p_para_tc->Rebin(rebin);
  p_para_ac->Rebin(rebin);    

  p_tot->Rebin(rebin);
  p_tot0->Rebin(rebin);
  p_tot_tc->Rebin(rebin);
  p_tot_ac->Rebin(rebin);  
  
  tke_gr->Rebin(rebin);
  tke_gr0->Rebin(rebin);                                                                                                                                    
  tke_gr_tc->Rebin(rebin);                                                                                                                                  
  tke_gr_ac->Rebin(rebin);

  tke_las->Rebin(rebin);
  tke_las0->Rebin(rebin);
  tke_las_tc->Rebin(rebin);                                                                                                                                 
  tke_las_ac->Rebin(rebin);
  
  TFile *fout = new TFile(Form("macro/ppx/output_momentum/%s_%s.root",reaction.c_str(),target.c_str()),"RECREATE");

  fout->Add(p_perp);
  fout->Add(p_perp0);

  fout->Add(p_para);
  fout->Add(p_para0);
  
  fout->Add(p_tot);
  fout->Add(p_tot0);

  fout->Add(tke_gr);
  fout->Add(tke_gr0);

  fout->Add(tke_las);
  fout->Add(tke_las0);  

  
  p_perp->Write();
  p_perp0->Write();
  p_perp_tc->Write();
  p_perp_ac->Write();
  
  p_para->Write();
  p_para0->Write();
  p_para_tc->Write();
  p_para_ac->Write();


  p_tot->Write();
  p_tot0->Write();
  p_tot_tc->Write();
  p_tot_ac->Write();

  
  tke_gr->Write();
  tke_gr0->Write();
  tke_gr_tc->Write();
  tke_gr_ac->Write();

  tke_las->Write();
  tke_las0->Write();
  tke_las_tc->Write();
  tke_las_ac->Write();

  //fout->Close();

}


