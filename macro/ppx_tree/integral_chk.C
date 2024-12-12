double calc_integral(TH1F *h,double min, double max);
double calc_err(TH1F *h,double min, double max);
int integral_chk(std::string  reaction,std::string  target){

  double integral_range[2]={-1.0,10.0};
  TFile *file_Ca = TFile::Open(Form("output/calib_pid/hist_ex/%s_%s_%s.root",reaction.c_str(),target.c_str(),target.c_str()),"read");
  TFile *file_mylar = TFile::Open(Form("output/calib_pid/hist_ex/%s_%s_%s.root",reaction.c_str(),"mylar",target.c_str()),"read");
  TFile *file_carbon = TFile::Open(Form("output/calib_pid/hist_ex/%s_%s_%s.root",reaction.c_str(),"carbon",target.c_str()),"read");
  Double_t scale_carbon=0.66348429*(48.0080/10.47)/(12.0/10.65);
  Double_t scale_oxygen=0.0;

  if(reaction=="pph"){
    integral_range[0]=-0.2*3.0;
  }else if(reaction=="ppt"){
    integral_range[0]=-0.37*3.0;
  }else if(reaction=="pph_48Ca"){
    integral_range[0]=-0.37*3.0;
  }else{
    std::cout << "Reaction input is invalid!" << std::endl;
    return 1;
  }
  
  if(target=="40Ca"){
    scale_oxygen=(0.21808865/(11.8/39.962))*0.0943;
  }else if(target=="42Ca"){
    scale_oxygen=(0.21808865/(10.0/41.958))*0.449;
  }else if(target=="44Ca"){
    scale_oxygen=(0.21808865/(9.7/43.955))*0.284;
  }else if(target=="48Ca"){
    scale_oxygen=(0.21808865/(10.0/47.952))*0.329;
  }else{
    std::cout << "Target input is invalid!" << std::endl;
    return 2;
  }


  TH1F *h_Ca = (TH1F*)file_Ca->Get("sx")->Clone("h_Ca");
  TH1F *h_mylar = (TH1F*)file_mylar->Get("sx")->Clone("h_mylar");
  TH1F *h_carbon = (TH1F*)file_carbon->Get("sx")->Clone("h_carbon");

  TH1F *h = (TH1F*)file_Ca->Get("sx")->Clone("h");
  TH1F *h_oxygen = (TH1F*)file_mylar->Get("sx")->Clone("h_oxygen");
  TH1F *h_carbon_scale = (TH1F*)file_carbon->Get("sx")->Clone("h_carbon_scale");

  h_carbon_scale->Scale(scale_carbon);
  h_oxygen->Add(h_carbon_scale,-1.0);
  h_oxygen->Scale(scale_oxygen);
  h->Add(h_oxygen,-1.0);
  
  double Integral_Ca=calc_integral(h_Ca,integral_range[0],integral_range[1]);
  double Integral_mylar=calc_integral(h_mylar,integral_range[0],integral_range[1]);
  double Integral_carbon=calc_integral(h_carbon,integral_range[0],integral_range[1]);
  double Integral=Integral_Ca-scale_oxygen*(Integral_mylar-scale_carbon*Integral_carbon);
  
  double Err_Ca=calc_err(h_Ca,integral_range[0],integral_range[1]);
  double Err_mylar=calc_err(h_mylar,integral_range[0],integral_range[1]);
  double Err_carbon=calc_err(h_carbon,integral_range[0],integral_range[1]);
  double Err=sqrt(pow(Err_Ca,2.0) + pow(scale_oxygen,2.0)*pow(Err_mylar,2.0) + pow(scale_oxygen*scale_carbon,2.0)*pow(Err_carbon,2.0));

  std::cout << "***** calculation by each  hist (Ca/mylar/carbon) *****" << std::endl; 
  std::cout << "Integral : " <<  Integral << std::endl;
  std::cout << "  Eroor  : " <<  Err      << std::endl;
  std::cout << "Err/Integral (%) : " <<  Err/Integral*100.0 << std::endl;

  std::cout << "***** calculation by merged hist *****" << std::endl;
  std::cout << "Integral test : " << h->Integral(h->FindBin(-0.37*3.0),h->FindBin(10.0)) << std::endl;  
  std::cout << "Integral : " << calc_integral(h,integral_range[0],integral_range[1]) << std::endl;
  std::cout << "Error    : " << calc_err(h,integral_range[0],integral_range[1]) << std::endl;;
  std::cout << "Err/Integral (%) : " <<  calc_err(h,integral_range[0],integral_range[1])/calc_integral(h,integral_range[0],integral_range[1])*100.0 << std::endl;
  return 0;

}  


  
double calc_integral(TH1F *h,double min, double max){

  double val_integral=0.0;
  int MinBin=h->FindBin(min);
  int MaxBin=h->FindBin(max);
  for(int i=MinBin;i<=MaxBin;i++){
      val_integral +=h->GetBinContent(i);
  }  
  return val_integral;
}


double calc_err(TH1F *h,double min, double max){

  double val_err=0.0;
  
  int MinBin=h->FindBin(min);
  int MaxBin=h->FindBin(max);
  for(int i=MinBin;i<=MaxBin;i++){
    double bin_err=h->GetBinError(i);
    val_err += pow(bin_err,2.0);
  }  
  return sqrt(val_err);
}
