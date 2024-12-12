double calc_integral(TH1F *h,double min, double max);
double calc_err(TH1F *h,double min, double max);
void integral(void){

  double ppt_range[2]={-1.0,12.0};
  double pph_range[2]={-1.0,12.0};
  double pph_48Ca_range[2]={-1.0,12.0};  

  //ppt
  TFile *file_40Ca_ppt = TFile::Open("output/ppx_ex_nogate/ppt_40Ca.weight.root ");
  TFile *file_42Ca_ppt = TFile::Open("output/ppx_ex_nogate/ppt_42Ca.weight.root ");
  TFile *file_44Ca_ppt = TFile::Open("output/ppx_ex_nogate/ppt_44Ca.weight.root ");
  TFile *file_48Ca_ppt = TFile::Open("output/ppx_ex_nogate/ppt_48Ca.weight.root ");

  TH1F *h_40Ca_ppt = (TH1F*)file_40Ca_ppt->Get("sx_weight")->Clone("h_40Ca_ppt");
  TH1F *h_42Ca_ppt = (TH1F*)file_42Ca_ppt->Get("sx_weight")->Clone("h_42Ca_ppt");
  TH1F *h_44Ca_ppt = (TH1F*)file_44Ca_ppt->Get("sx_weight")->Clone("h_44Ca_ppt");
  TH1F *h_48Ca_ppt = (TH1F*)file_48Ca_ppt->Get("sx_weight")->Clone("h_48Ca_ppt");

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
  TFile *file_40Ca_pph = TFile::Open("output/ppx_ex_nogate/pph_40Ca.weight.root ");
  TFile *file_42Ca_pph = TFile::Open("output/ppx_ex_nogate/pph_42Ca.weight.root ");
  TFile *file_44Ca_pph = TFile::Open("output/ppx_ex_nogate/pph_44Ca.weight.root ");
  TFile *file_48Ca_pph = TFile::Open("output/ppx_ex_nogate/pph_48Ca.weight.root ");

  TH1F *h_40Ca_pph = (TH1F*)file_40Ca_pph->Get("sx_weight")->Clone("h_40Ca_pph");
  TH1F *h_42Ca_pph = (TH1F*)file_42Ca_pph->Get("sx_weight")->Clone("h_42Ca_pph");
  TH1F *h_44Ca_pph = (TH1F*)file_44Ca_pph->Get("sx_weight")->Clone("h_44Ca_pph");
  TH1F *h_48Ca_pph = (TH1F*)file_48Ca_pph->Get("sx_weight")->Clone("h_48Ca_pph");

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
