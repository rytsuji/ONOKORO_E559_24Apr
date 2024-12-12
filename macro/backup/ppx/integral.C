double calc_integral(TH1F *h,double min, double max);
double calc_err(TH1F *h,double min, double max);
void integral(void){

  //double ppt_range[2]={15.0,32.0};
  //double pph_range[2]={15.0,32.0};
  //double pph_48Ca_range[2]={28.0,43.0};
  double ppt_range[2]={15.0,34.0};
  double pph_range[2]={15.0,34.0};
  double pph_48Ca_range[2]={28.0,45.0};
  
  
  //ppt
  Double_t scale_mylar_carbon=0.66348429*(48.0080/10.47)/(12.0/10.65);
  Double_t scale_oxygen_40Ca=(0.21808865/(11.8/39.962))*0.0943;
  Double_t scale_oxygen_42Ca=(0.21808865/(10.0/41.958))*0.449;
  Double_t scale_oxygen_44Ca=(0.21808865/(9.7/43.955))*0.284;
  Double_t scale_oxygen_48Ca=(0.21808865/(10.0/47.952))*0.329;
  
  
  TFile *file_mylar_ppt = TFile::Open("output/ppx/ppt_mylar.weight.root ");  
  TFile *file_carbon_ppt = TFile::Open("output/ppx/ppt_carbon.weight.root ");
  TFile *file_40Ca_ppt = TFile::Open("output/ppx/ppt_40Ca.weight.root ");
  TFile *file_42Ca_ppt = TFile::Open("output/ppx/ppt_42Ca.weight.root ");
  TFile *file_44Ca_ppt = TFile::Open("output/ppx/ppt_44Ca.weight.root ");
  TFile *file_48Ca_ppt = TFile::Open("output/ppx/ppt_48Ca.weight.root ");


  
  TH1F *h_mylar_ppt = (TH1F*)file_mylar_ppt->Get("sx_tave")->Clone("h_mylar_ppt");
  TH1F *h_carbon_ppt = (TH1F*)file_carbon_ppt->Get("sx_tave")->Clone("h_carbon_ppt");
  TH1F *h_40Ca_ppt = (TH1F*)file_40Ca_ppt->Get("sx_tave")->Clone("h_40Ca_ppt");
  TH1F *h_42Ca_ppt = (TH1F*)file_42Ca_ppt->Get("sx_tave")->Clone("h_42Ca_ppt");
  TH1F *h_44Ca_ppt = (TH1F*)file_44Ca_ppt->Get("sx_tave")->Clone("h_44Ca_ppt");
  TH1F *h_48Ca_ppt = (TH1F*)file_48Ca_ppt->Get("sx_tave")->Clone("h_48Ca_ppt");


  Double_t integral_mylar_ppt=calc_integral(h_mylar_ppt,ppt_range[0],ppt_range[1]);
  Double_t integral_carbon_ppt=calc_integral(h_carbon_ppt,ppt_range[0],ppt_range[1]);
  Double_t integral_40Ca_ppt=calc_integral(h_40Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t integral_42Ca_ppt=calc_integral(h_42Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t integral_44Ca_ppt=calc_integral(h_44Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t integral_48Ca_ppt=calc_integral(h_48Ca_ppt,ppt_range[0],ppt_range[1]);

  Double_t err_mylar_ppt=calc_err(h_mylar_ppt,ppt_range[0],ppt_range[1]);
  Double_t err_carbon_ppt=calc_err(h_carbon_ppt,ppt_range[0],ppt_range[1]);
  Double_t err_40Ca_ppt=calc_err(h_40Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t err_42Ca_ppt=calc_err(h_42Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t err_44Ca_ppt=calc_err(h_44Ca_ppt,ppt_range[0],ppt_range[1]);
  Double_t err_48Ca_ppt=calc_err(h_48Ca_ppt,ppt_range[0],ppt_range[1]);

  Double_t integral_oxygen=integral_mylar_ppt-scale_mylar_carbon*integral_carbon_ppt;
  std::cout << "****  ppt integral raw ****" << std::endl;
  std::cout << "Mylar: " <<integral_mylar_ppt << std::endl;
  std::cout << "natC: " << integral_carbon_ppt << std::endl;
  std::cout << "40Ca: " << integral_40Ca_ppt << std::endl;
  std::cout << "42Ca: " << integral_42Ca_ppt << std::endl;
  std::cout << "44Ca: " << integral_44Ca_ppt << std::endl;
  std::cout << "48Ca: " << integral_48Ca_ppt << std::endl;
  
  double TotalErr_40Ca_ppt=sqrt(pow(err_40Ca_ppt,2.0)+pow(scale_oxygen_40Ca,2.0)*(pow(err_mylar_ppt,2.0)+pow(scale_mylar_carbon*err_carbon_ppt,2.0)));
  double TotalErr_42Ca_ppt=sqrt(pow(err_42Ca_ppt,2.0)+pow(scale_oxygen_42Ca,2.0)*(pow(err_mylar_ppt,2.0)+pow(scale_mylar_carbon*err_carbon_ppt,2.0)));
  double TotalErr_44Ca_ppt=sqrt(pow(err_44Ca_ppt,2.0)+pow(scale_oxygen_44Ca,2.0)*(pow(err_mylar_ppt,2.0)+pow(scale_mylar_carbon*err_carbon_ppt,2.0)));
  double TotalErr_48Ca_ppt=sqrt(pow(err_44Ca_ppt,2.0)+pow(scale_oxygen_48Ca,2.0)*(pow(err_mylar_ppt,2.0)+pow(scale_mylar_carbon*err_carbon_ppt,2.0)));

  
  
  //pph
  TFile *file_mylar_pph = TFile::Open("output/ppx/pph_mylar.weight.root ");  
  TFile *file_carbon_pph = TFile::Open("output/ppx/pph_carbon.weight.root ");
  TFile *file_40Ca_pph = TFile::Open("output/ppx/pph_40Ca.weight.root ");
  TFile *file_42Ca_pph = TFile::Open("output/ppx/pph_42Ca.weight.root ");
  TFile *file_44Ca_pph = TFile::Open("output/ppx/pph_44Ca.weight.root ");

  TFile *file_48Ca_mylar_pph = TFile::Open("output/ppx/pph_48Ca_mylar.weight.root ");
  TFile *file_48Ca_carbon_pph = TFile::Open("output/ppx/pph_48Ca_carbon.weight.root ");
  TFile *file_48Ca_pph = TFile::Open("output/ppx/pph_48Ca_48Ca.weight.root ");


  
  TH1F *h_mylar_pph = (TH1F*)file_mylar_pph->Get("sx_tave")->Clone("h_mylar_pph");
  TH1F *h_carbon_pph = (TH1F*)file_carbon_pph->Get("sx_tave")->Clone("h_carbon_pph");
  TH1F *h_40Ca_pph = (TH1F*)file_40Ca_pph->Get("sx_tave")->Clone("h_40Ca_pph");
  TH1F *h_42Ca_pph = (TH1F*)file_42Ca_pph->Get("sx_tave")->Clone("h_42Ca_pph");
  TH1F *h_44Ca_pph = (TH1F*)file_44Ca_pph->Get("sx_tave")->Clone("h_44Ca_pph");

  TH1F *h_48Ca_mylar_pph = (TH1F*)file_48Ca_mylar_pph->Get("sx_tave")->Clone("h_48Ca_mylar_pph");
  TH1F *h_48Ca_carbon_pph = (TH1F*)file_48Ca_carbon_pph->Get("sx_tave")->Clone("h_48Ca_carbon_pph");
  TH1F *h_48Ca_pph = (TH1F*)file_48Ca_pph->Get("sx_tave")->Clone("h_48Ca_pph");

  Double_t integral_mylar_pph=calc_integral(h_mylar_pph,pph_range[0],pph_range[1]);
  Double_t integral_carbon_pph=calc_integral(h_carbon_pph,pph_range[0],pph_range[1]);
  Double_t integral_40Ca_pph=calc_integral(h_40Ca_pph,pph_range[0],pph_range[1]);
  Double_t integral_42Ca_pph=calc_integral(h_42Ca_pph,pph_range[0],pph_range[1]);
  Double_t integral_44Ca_pph=calc_integral(h_44Ca_pph,pph_range[0],pph_range[1]);

  Double_t integral_48Ca_mylar_pph=calc_integral(h_48Ca_mylar_pph,pph_48Ca_range[0],pph_48Ca_range[1]);
  Double_t integral_48Ca_carbon_pph=calc_integral(h_48Ca_carbon_pph,pph_48Ca_range[0],pph_48Ca_range[1]);
  Double_t integral_48Ca_pph=calc_integral(h_48Ca_pph,pph_48Ca_range[0],pph_48Ca_range[1]);

  Double_t err_mylar_pph=calc_err(h_mylar_pph,pph_range[0],pph_range[1]);
  Double_t err_carbon_pph=calc_err(h_carbon_pph,pph_range[0],pph_range[1]);
  Double_t err_40Ca_pph=calc_err(h_40Ca_pph,pph_range[0],pph_range[1]);
  Double_t err_42Ca_pph=calc_err(h_42Ca_pph,pph_range[0],pph_range[1]);
  Double_t err_44Ca_pph=calc_err(h_44Ca_pph,pph_range[0],pph_range[1]);

  Double_t err_48Ca_mylar_pph=calc_err(h_48Ca_mylar_pph,pph_48Ca_range[0],pph_48Ca_range[1]);
  Double_t err_48Ca_carbon_pph=calc_err(h_48Ca_carbon_pph,pph_48Ca_range[0],pph_48Ca_range[1]);
  Double_t err_48Ca_pph=calc_err(h_48Ca_pph,pph_48Ca_range[0],pph_48Ca_range[1]);

  Double_t integral_oxygen_pph=integral_mylar_pph-scale_mylar_carbon*integral_carbon_pph;
  Double_t integral_48Ca_oxygen=integral_48Ca_mylar_pph-scale_mylar_carbon*integral_48Ca_carbon_pph;

  

  std::cout << "****  pph integral raw ****" << std::endl;
  std::cout << "Mylar: " <<integral_mylar_pph << std::endl;
  std::cout << "natC: " << integral_carbon_pph << std::endl;
  std::cout << "40Ca: " << integral_40Ca_pph << std::endl;
  std::cout << "42Ca: " << integral_42Ca_pph << std::endl;
  std::cout << "44Ca: " << integral_44Ca_pph << std::endl;
  //std::cout << "44Ca: " << h_44Ca_pph->Integral(h_44Ca_pph->FindBin(15.0),h_44Ca_pph->FindBin(34.0)) << std::endl;

  std::cout << "Mylar(48Ca): " << integral_48Ca_mylar_pph << std::endl;
  std::cout << "natC(48Ca): " << integral_48Ca_carbon_pph << std::endl;
  std::cout << "48Ca: " << integral_48Ca_pph << std::endl;


  double TotalErr_40Ca_pph=sqrt(pow(err_40Ca_pph,2.0)+pow(scale_oxygen_40Ca,2.0)*(pow(err_mylar_pph,2.0)+pow(scale_mylar_carbon*err_carbon_pph,2.0)));
  double TotalErr_42Ca_pph=sqrt(pow(err_42Ca_pph,2.0)+pow(scale_oxygen_42Ca,2.0)*(pow(err_mylar_pph,2.0)+pow(scale_mylar_carbon*err_carbon_pph,2.0)));
  double TotalErr_44Ca_pph=sqrt(pow(err_44Ca_pph,2.0)+pow(scale_oxygen_44Ca,2.0)*(pow(err_mylar_pph,2.0)+pow(scale_mylar_carbon*err_carbon_pph,2.0)));
  double TotalErr_48Ca_pph=sqrt(pow(err_48Ca_pph,2.0)+pow(scale_oxygen_48Ca,2.0)*(pow(err_48Ca_mylar_pph,2.0)+pow(scale_mylar_carbon*err_48Ca_carbon_pph,2.0)));



  std::cout << "****  ppt integral****" << std::endl;
  std::cout << "16O: " << integral_oxygen << std::endl;
  std::cout << "40Ca: " << integral_40Ca_ppt-scale_oxygen_40Ca*integral_oxygen <<  " " <<  TotalErr_40Ca_ppt << std::endl;
  std::cout << "42Ca: " << integral_42Ca_ppt-scale_oxygen_42Ca*integral_oxygen <<  " " <<  TotalErr_42Ca_ppt << std::endl;
  std::cout << "44Ca: " << integral_44Ca_ppt-scale_oxygen_44Ca*integral_oxygen <<  " " <<  TotalErr_44Ca_ppt << std::endl;
  std::cout << "48Ca: " << integral_48Ca_ppt-scale_oxygen_48Ca*integral_oxygen <<  " " <<  TotalErr_48Ca_ppt << std::endl;


  
  std::cout << "****  pph integral****" << std::endl;
  std::cout << "16O: " << integral_oxygen_pph << std::endl;
  std::cout << "40Ca: " << integral_40Ca_pph-scale_oxygen_40Ca*integral_oxygen_pph << " " <<  TotalErr_40Ca_pph << std::endl;
  std::cout << "42Ca: " << integral_42Ca_pph-scale_oxygen_42Ca*integral_oxygen_pph << " " <<  TotalErr_42Ca_pph << std::endl;
  std::cout << "44Ca: " << integral_44Ca_pph-scale_oxygen_44Ca*integral_oxygen_pph << " " <<  TotalErr_44Ca_pph << std::endl;
  std::cout << "48Ca: " << integral_48Ca_pph-scale_oxygen_48Ca*integral_48Ca_oxygen << " " <<  TotalErr_48Ca_pph <<std::endl;  

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
