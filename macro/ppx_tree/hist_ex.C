#include <yaml-cpp/yaml.h>

double dTGRcorr(double SxVal, double Tinc, double TMinGR, double TMaxGR, double TMinLAS, double TMaxLAS);
Double_t GRand(Double_t sigma);
int hist_ex(std::string  reaction,std::string  target,std::string Sx){
  
  //scale of accidental coincidence 
  double scale_acc=1.0/8.0;
  //double scale_acc=1.0/6.0;
  int nBin=1200;
  double xMin=-30.0;
  double xMax=30.0;

  //Stat Error check
  double Integral_range[2]={-1.0,10.0};
  double Integral_signal=0.0;
  double Integral_noise=0.0;
  double StatError_signal2=0.0;
  double StatError_noise2=0.0;
  
  //input check
  if(reaction != "ppt" && reaction != "pph" && reaction != "pph_48Ca"){
    std::cout << "Reaction input is invalid!(ppt or pph or pph_48Ca)" << std::endl;
    return 1;
  }
  
  if(target !="40Ca"  && target !="42Ca"  && target !="44Ca"  && target !="48Ca"  && target != "carbon" && target != "mylar"){
    std::cout << "Target input is invalid!(mylar or carbon or 40-48Ca)" << std::endl;
    return 1;
  }
  //Sx
  Double_t SxVal=0.0;
  if(reaction == "ppt"){
    if(Sx=="40Ca"){
      SxVal=24.996;
    }else if(Sx=="42Ca"){
      SxVal=19.690;
    }else if(Sx=="44Ca"){
      SxVal=20.859;
    }else if(Sx=="48Ca"){
      SxVal=22.559;
    }else if(Sx=="carbon"){
      SxVal=27.366;
    }else if(Sx=="oxygen"){
      SxVal=25.032;
    }
  }else if(reaction == "pph" || reaction == "pph_48Ca"){
    if(Sx=="40Ca"){
      SxVal=18.830;
    }else if(Sx=="42Ca"){
      SxVal=20.236;
    }else if(Sx=="44Ca"){
      SxVal=23.332;
    }else if(Sx=="48Ca"){
      SxVal=29.385;
    }else if(Sx=="carbon"){
      SxVal=26.280;
    }else if(Sx=="oxygen"){
      SxVal=22.793;
    }
  }

  std::cout << "Sx(" << Sx << " " << reaction << ") : " << SxVal << " (MeV)" <<std::endl; 
  
  //Prm & Gate
  std::ifstream file_config(Form("macro/ppx_tree/prm/%s_%s.yaml",reaction.c_str(),target.c_str()));
  YAML::Node node  = YAML::Load(file_config);

  Double_t Tinc = node["Tinc"].as<Double_t>();
  Double_t TMinGR = node["TMinGR"].as<Double_t>();
  Double_t TMaxGR = node["TMaxGR"].as<Double_t>();
  Double_t TMinLAS = node["TMinLAS"].as<Double_t>();
  Double_t TMaxLAS = node["TMaxLAS"].as<Double_t>();
  Double_t OmegaGR = node["OmegaGR"].as<Double_t>();
  Double_t OmegaLAS = node["OmegaLAS"].as<Double_t>();
  Double_t scale = 1.0;//node["scale"].as<Double_t>();
  Double_t offset = node["offset"].as<Double_t>(); //Offset of Sx
  Double_t sigma = node["sigma"].as<Double_t>();  //change resolution of Sx
  
  std::string fName  = node["fName"].as<std::string>();        
  Double_t dTGR=TMaxGR-TMinGR;

  TCut AGR = Form("%s",(node["angGR"].as<std::string>()).c_str());
  TCut ALAS = Form("%s",(node["angLAS"].as<std::string>()).c_str());
  TCut TGR=Form("abs(pgr.fTKE>%f && pgr.fTKE <%f)",TMinGR,TMaxGR);
  TCut TLAS=Form("abs(plas.fTKE>%f && plas.fTKE <%f)",TMinLAS,TMaxLAS);  

  TCut TC="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))>-35 && (tof.fTiming-(pgr.GetTOF()-plas.GetTOF()))<35";
  //TCut AC="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>-320 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<-100) || (tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>100 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<320)";
  TCut AC="(tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>-320 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<-35) || (tof.fTiming-(pgr.GetTOF()-plas.GetTOF())>35 && tof.fTiming-(pgr.GetTOF()-plas.GetTOF())<320)";
  
  //read runlist
  std::vector<std::string> run;
  ifstream runlist(Form("runlist/%s/runlist_%s.txt",reaction.c_str(),target.c_str()));
  std::string line_runlist;  
  while(getline(runlist,line_runlist)){
    run.push_back(line_runlist);
  }

  const int n_file = run.size();
  TH1F* ht[n_file];  
  TH1F* ha[n_file];
  TH1F* hs[n_file];  

  //BI
  double TotalBI=0.0;
  double TotalTime=0.0;



  /********* Make Histograms Run by Run *********/
  for(int i=0;i<n_file;i++){
    std::cout << "***** processing run"  << run[i]  << " *****" <<std::endl;         

    Double_t eff=1.0;    
    //hist phys
    TFile *ifile = TFile::Open(Form("output/calib_pid/run%s.root",run[i].c_str()),"read");    
    TTree* tree = ((TTree*)ifile->Get("tree"));
    ht[i] = new TH1F(Form("ht[%d]",i),"",nBin,xMin,xMax);
    ha[i] = new TH1F(Form("ha[%d]",i),"",nBin,xMin,xMax);
    hs[i] = new TH1F(Form("hs[%d]",i),"",nBin,xMin,xMax);        


    
    tree->Draw(Form("%f-pgr.fTKE-plas.fTKE-%f+%f+GRand(%f)>>ht[%d]",Tinc,SxVal,offset,sigma,i),
	       AGR && ALAS && TGR && TLAS && TC,
	       //( AGR && ALAS && TGR && TLAS && TC)*Form("dTGRcorr(%f-pgr.fTKE-plas.fTKE,%f,%f,%f,%f,%f)",Tinc,Tinc,TMinGR,TMaxGR,TMinLAS,TMaxLAS),
	       "goff");
    tree->Draw(Form("%f-pgr.fTKE-plas.fTKE-%f+%f+GRand(%f)>>ha[%d]",Tinc,SxVal,offset,sigma,i),
	       AGR && ALAS && TGR && TLAS && AC,
	       //( AGR && ALAS && TGR && TLAS && AC)*Form("dTGRcorr(%f-pgr.fTKE-plas.fTKE,%f,%f,%f,%f,%f)",Tinc,Tinc,TMinGR,TMaxGR,TMinLAS,TMaxLAS),
	       "goff");

    double Integral_signal_1run = ht[i]->Integral(ht[i]->FindBin(Integral_range[0]),ht[i]->FindBin(Integral_range[1]));
    double Integral_noise_1run  = ha[i]->Integral(ha[i]->FindBin(Integral_range[0]),ha[i]->FindBin(Integral_range[1]));


    
    ht[i]->Sumw2();
    ha[i]->Sumw2();
    
    hs[i]->Add(ht[i],1.0);
    hs[i]->Add(ha[i],-scale_acc);
    //hs[i]->Sumw2(0);
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
    eff_vdc_las=eff_las_x1*eff_las_x2*(eff_las_u1*eff_las_u2+(1- eff_las_u1*eff_las_u2)*eff_las_v1*eff_las_v2);
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
    eff_daq= kg/mg;

    std::cout << "  Live/Trigger (count/s), eff DAQ"  << std::endl;
    std::cout << " GR   : " << kg  << "  " << mg <<  "  " << kg/mg << std::endl;
    std::cout << " LAS  : " << kl  << "  "  << ml << "  " << kl/ml << std::endl;

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
    std::cout << "Beam Charge (nC): " << BI << std::endl;    
    std::cout << "Beam Current (nA): " << BI/dT << std::endl;

    //scale histograms by efficiency
    eff=eff_mhit_las*eff_mhit_gr*eff_vdc_gr*eff_vdc_las*eff_daq;
    ht[i]->Scale(1.0/eff);    
    ha[i]->Scale(scale_acc/eff);    
    std::cout << "Total efficiency: " << eff << std::endl;
    
    std::cout << "ht[" << i << "] integral/eff       : " << Integral_signal_1run/eff << std::endl;
    std::cout << "ha[" << i << "] integral/(8.0*eff) : " << Integral_noise_1run/(8.0*eff) << std::endl;
    std::cout << "S/N ratio      : " << Integral_signal_1run/(Integral_noise_1run/8.0) << std::endl;
    std::cout << "Eroor ht[" << i << "] sqrt(integral)/eff : " << sqrt(Integral_signal_1run)/eff << std::endl;
    std::cout << "ha[" << i << "] sqrt(integral)/(8.0*eff) : " << sqrt(Integral_noise_1run)/(8.0*eff) << std::endl;    

    Integral_signal += Integral_signal_1run/eff;
    Integral_noise += Integral_noise_1run/(8.0*eff);
    StatError_signal2 += Integral_signal_1run/pow(eff,2.0);
    StatError_noise2 += Integral_noise_1run/pow(8.0*eff,2.0);    
    
    //delete ifile; 
    //delete tree;   
  }  
  /********* End of Making Histograms Run by Run *********/    


  //target thhickness
  fstream target_info(Form("macro/ppx_tree/target/%s.txt",target.c_str()));
  std::string line_target;
  getline(target_info,line_target);
  std::istringstream strs_target(line_target);
  std::string str_thick;
  std::string str_Aweight;
  strs_target  >> str_thick >> str_Aweight;
  Double_t thick=std::stod(str_thick);
  Double_t Aweight=std::stod(str_Aweight);
  Double_t targetTilted=1.0/cos(60.0*TMath::DegToRad());

  Double_t NA=6.0221407610e+23;
  Double_t eu=1.602176634e-19;
  Double_t scale_tdx_ub=(1.0e+30)/((OmegaGR*OmegaLAS*dTGR) * (TotalBI*(1.0e-9)/eu) * (targetTilted*thick*(1.0e-3)*NA/Aweight));

  std::cout << "-----------------------" << std::endl;
  std::cout  << "  Beam Current (nA)  : " << TotalBI/TotalTime << std::endl;  
  std::cout  << "  Beam Charge  (nC)  : " << TotalBI << std::endl;
  std::cout  << "   target   (mg/cm2) : " << thick << std::endl;
  std::cout  << "   target   (g/mol)  : " << Aweight << std::endl;
  std::cout  << " target tilte factor : " << targetTilted << std::endl;  
  std::cout  << "     dE GR    (MeV)  : " << dTGR << std::endl;
  std::cout  << "solid ang GR  (str)  : " << OmegaGR << std::endl;
  std::cout  << "solid ang LAS (str)  : " << OmegaLAS << std::endl;      
  std::cout << "Scaling factor to TDX : " <<  scale_tdx_ub << std::endl;
  std::cout << "Integration of signal : " <<  Integral_signal << std::endl;
  std::cout << "Integration of noise  : " <<  Integral_noise << std::endl;
  std::cout << "Integration sig-noise : " <<  Integral_signal-Integral_noise << std::endl;
  std::cout << " StatError  of signal : " <<  sqrt(StatError_signal2) << std::endl;
  std::cout << " StatEroor  of noise  : " <<  sqrt(StatError_noise2) << std::endl;
  std::cout << " TotalStatEroor (%)   : " << sqrt(StatError_signal2+StatError_noise2)/(Integral_signal-Integral_noise)*100.0 << std::endl; 


  //Adding Histograns
  TH1F *sx_tc=new TH1F("sx_tc", "true coin",nBin,xMin,xMax);
  TH1F *sx_ac=new TH1F("sx_ac", "accidental coin",nBin,xMin,xMax);
  TH1F *sx_tc0=new TH1F("sx_tc0", "true coin",nBin,xMin,xMax);
  TH1F *sx_ac0=new TH1F("sx_ac0", "accidental coin",nBin,xMin,xMax);
  sx_tc->Sumw2();
  sx_ac->Sumw2();
  for(int i=0;i<n_file;i++){
    sx_tc->Add(ht[i],1.0);
    sx_ac->Add(ha[i],1.0);
  }
  sx_tc0->Add(sx_tc,1.0);
  sx_ac0->Add(sx_ac,1.0);
  sx_tc0->Sumw2(0);
  sx_ac0->Sumw2(0);
  //sx_tc->Scale(scale_tdx_ub*scale);
  //sx_ac->Scale(scale_tdx_ub*scale);


  TH1F *sx=new TH1F("sx", "sx",nBin,xMin,xMax);
  sx->Sumw2();
  sx->Add(sx_tc,1.0);
  sx->Add(sx_ac,-1.0);
  sx->Scale(scale_tdx_ub*scale);
  
  TH1F *sx0=new TH1F("sx0", "sx0",nBin,xMin,xMax);
  sx0->Add(sx,1.0);
  sx0->Sumw2(0);


  //Draw Histo
  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("ht sx E1");
  sx0->Draw("same");
  




  //Write to File
  TFile *fout = new TFile(Form("output/calib_pid/hist_ex/%s_%s_%s.root",reaction.c_str(),target.c_str(),Sx.c_str()),"RECREATE");
  //TFile *fout = new TFile(Form("output/calib_pid/hist_ex/%s",fName.c_str()),"RECREATE");

  
  for(int i=0;i<n_file;i++){
    ht[i]->Sumw2(0);
    ha[i]->Sumw2(0);
    ha[i]->SetLineColor(2);
    ht[i]->Write();        
    ha[i]->Write();
    hs[i]->Write();        
  }
    
  sx->Write();
  sx0->Write();

  sx_ac->SetLineColor(2);
  sx_ac->SetMarkerColor(2);  
  sx_ac0->SetLineColor(2);

  sx_tc->Write();
  sx_ac->Write();
  sx_tc0->Write();
  sx_ac0->Write();    

  //fout->Close();
  //std::cout << dTGRcorr(,Tinc,TMinGR,TMaxGR,TMinLAS,TMaxLAS) << std::endl;
  return 0;
}


double dTGRcorr(double SxVal, double Tinc, double TMinGR, double TMaxGR, double TMinLAS, double TMaxLAS){
  double scale=0.0;

  double dTpGR=TMaxGR-TMinGR;
  double CutOff=2.0;
  
  double Sx[4]={Tinc-TMaxGR-TMaxLAS,
		min(Tinc-TMinGR-TMaxLAS,Tinc-TMaxGR-TMinLAS),
		max(Tinc-TMinGR-TMaxLAS,Tinc-TMaxGR-TMinLAS),
		Tinc-TMinGR-TMinLAS};

  if(SxVal<=Sx[0]+CutOff){
    scale=0.0;
    }else if(SxVal<=Sx[1]){
      scale=dTpGR/(SxVal-Sx[0]);
    }else if(SxVal<=Sx[2]){
      scale=1.0;
    }else if(SxVal<Sx[3]-CutOff){
      scale=dTpGR/(Sx[3]-SxVal);
    }else{
      scale=0.0;
    }
  

  return scale;
}

Double_t GRand(Double_t sigma)
{     return gRandom->Gaus(0.0,sigma);   }
