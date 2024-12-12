double calc_integral(TH1F *h,double min, double max);
double calc_err(TH1F *h,double min, double max);
void integral_nogate(void){

  double ppt_range[2]={-2.0*3.0,10.0};
  double pph_range[2]={-3.7*3.0,10.0};
  double pph_48Ca_range[2]={-3.7*3.0,10.0};  

  //ppt
  TFile *file_40Ca_ppt = TFile::Open("output/calib_pid/hist_ex/ppt_40Ca.nogate.root ");
  TFile *file_42Ca_ppt = TFile::Open("output/calib_pid/hist_ex/ppt_42Ca.nogate.root ");
  TFile *file_44Ca_ppt = TFile::Open("output/calib_pid/hist_ex/ppt_44Ca.nogate.root ");
  TFile *file_48Ca_ppt = TFile::Open("output/calib_pid/hist_ex/ppt_48Ca.nogate.root ");

  TH1F *h_40Ca_ppt = (TH1F*)file_40Ca_ppt->Get("h_40Ca")->Clone("h_40Ca_ppt");
  TH1F *h_42Ca_ppt = (TH1F*)file_42Ca_ppt->Get("h_42Ca")->Clone("h_42Ca_ppt");
  TH1F *h_44Ca_ppt = (TH1F*)file_44Ca_ppt->Get("h_44Ca")->Clone("h_44Ca_ppt");
  TH1F *h_48Ca_ppt = (TH1F*)file_48Ca_ppt->Get("h_48Ca")->Clone("h_48Ca_ppt");

  Double_t integral_40Ca_ppt=calc_integral(h_40Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t integral_42Ca_ppt=calc_integral(h_42Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t integral_44Ca_ppt=calc_integral(h_44Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t integral_48Ca_ppt=calc_integral(h_48Ca_ppt,ppt_range[0],ppt_range[1]);

  Double_t err_40Ca_ppt=calc_err(h_40Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t err_42Ca_ppt=calc_err(h_42Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t err_44Ca_ppt=calc_err(h_44Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t err_48Ca_ppt=calc_err(h_48Ca_ppt,ppt_range[0],ppt_range[1]);

  std::cout << "****  ppt integral****" << std::endl;
  std::cout << "40Ca: " << integral_40Ca_ppt << " " << err_40Ca_ppt <<  std::endl;
  std::cout << "42Ca: " << integral_42Ca_ppt << " " << err_42Ca_ppt <<  std::endl;
  std::cout << "44Ca: " << integral_44Ca_ppt << " " << err_44Ca_ppt <<  std::endl;
  std::cout << "48Ca: " << integral_48Ca_ppt << " " << err_48Ca_ppt <<  std::endl;

  //ppt
  TFile *file_40Ca_pph = TFile::Open("output/calib_pid/hist_ex/pph_40Ca.nogate.root ");
  TFile *file_42Ca_pph = TFile::Open("output/calib_pid/hist_ex/pph_42Ca.nogate.root ");
  TFile *file_44Ca_pph = TFile::Open("output/calib_pid/hist_ex/pph_44Ca.nogate.root ");
  TFile *file_48Ca_pph = TFile::Open("output/calib_pid/hist_ex/pph_48Ca.nogate.root ");

  TH1F *h_40Ca_pph = (TH1F*)file_40Ca_pph->Get("h_40Ca")->Clone("h_40Ca_pph");
  TH1F *h_42Ca_pph = (TH1F*)file_42Ca_pph->Get("h_42Ca")->Clone("h_42Ca_pph");
  TH1F *h_44Ca_pph = (TH1F*)file_44Ca_pph->Get("h_44Ca")->Clone("h_44Ca_pph");
  TH1F *h_48Ca_pph = (TH1F*)file_48Ca_pph->Get("h_48Ca")->Clone("h_48Ca_pph");

  Double_t integral_40Ca_pph=calc_integral(h_40Ca_pph,pph_range[0],pph_range[1]);
  Double_t integral_42Ca_pph=calc_integral(h_42Ca_pph,pph_range[0],pph_range[1]);
  Double_t integral_44Ca_pph=calc_integral(h_44Ca_pph,pph_range[0],pph_range[1]);
  Double_t integral_48Ca_pph=calc_integral(h_48Ca_pph,pph_range[0],pph_range[1]);

  Double_t err_40Ca_pph=calc_err(h_40Ca_pph,pph_range[0],pph_range[1]);
  Double_t err_42Ca_pph=calc_err(h_42Ca_pph,pph_range[0],pph_range[1]);
  Double_t err_44Ca_pph=calc_err(h_44Ca_pph,pph_range[0],pph_range[1]);
  Double_t err_48Ca_pph=calc_err(h_48Ca_pph,pph_range[0],pph_range[1]);

  std::cout << "****  pph integral****" << std::endl;
  std::cout << "40Ca: " << integral_40Ca_pph << " " << err_40Ca_pph <<  std::endl;
  std::cout << "42Ca: " << integral_42Ca_pph << " " << err_42Ca_pph <<  std::endl;
  std::cout << "44Ca: " << integral_44Ca_pph << " " << err_44Ca_pph <<  std::endl;
  std::cout << "48Ca: " << integral_48Ca_pph << " " << err_48Ca_pph <<  std::endl;

  std::cout << "**** for copy and paste****" << std::endl;
  std::cout << "#MassNum TDX_ppt err_ppt TDX_pph err_pph nt_v1 nh_v1 nt_v2 nh_v2 DWIA_ppt DWIA_pph" << std::endl;
  std::cout << "40 " << integral_40Ca_ppt << " " << err_40Ca_ppt << " " << integral_40Ca_pph << " " << err_40Ca_pph << " 8.933709e-02 9.088110e-02 1.642564e-01 1.510936e-01 " <<"1.67 1.70" <<std::endl;
  std::cout << "42 " << integral_42Ca_ppt << " " << err_42Ca_ppt << " " << integral_42Ca_pph << " " << err_42Ca_pph << " 1.152084e-01 7.120290e-02 1.906213e-01 1.311510e-01 " << " 1.74 1.50" << std::endl;
  std::cout << "44 " << integral_44Ca_ppt << " " << err_44Ca_ppt << " " << integral_44Ca_pph << " " << err_44Ca_pph << " 9.119249e-02 3.287083e-02 1.642303e-01 9.005307e-02 " << " 1.70 1.31"<< std::endl;
  std::cout << "48 " << integral_48Ca_ppt << " " << err_48Ca_ppt << " " << integral_48Ca_pph << " " << err_48Ca_pph << " 4.580736e-03 0.0000000000 2.895080e-02 0.000000000 " << "1.58 0.92"<< std::endl;


}  


  
double calc_integral(TH1F *h,double min, double max){

  double val_integral=0.0;
  int MinBin=h->FindBin(min);
  int MaxBin=h->FindBin(max);
  for(int i=MinBin;i<MaxBin+1;i++){
      val_integral +=h->GetBinContent(i);
  }  
  return val_integral;
}


double calc_err(TH1F *h,double min, double max){

  double val_err=0.0;
  
  int MinBin=h->FindBin(min);
  int MaxBin=h->FindBin(max);
  for(int i=MinBin;i<MaxBin+1;i++){
      val_err +=pow(h->GetBinError(i),2.0);
  }  
  return sqrt(val_err);
}
