{
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

  Double_t integral_mylar_ppt=h_mylar_ppt->Integral(h_mylar_ppt->FindBin(18.0),h_mylar_ppt->FindBin(34.0));
  Double_t integral_carbon_ppt=h_carbon_ppt->Integral(h_carbon_ppt->FindBin(18.0),h_carbon_ppt->FindBin(34.0));
  Double_t integral_40Ca_ppt=h_40Ca_ppt->Integral(h_40Ca_ppt->FindBin(18.0),h_40Ca_ppt->FindBin(34.0));
  Double_t integral_42Ca_ppt=h_42Ca_ppt->Integral(h_42Ca_ppt->FindBin(18.0),h_42Ca_ppt->FindBin(34.0));
  Double_t integral_44Ca_ppt=h_44Ca_ppt->Integral(h_44Ca_ppt->FindBin(18.0),h_44Ca_ppt->FindBin(34.0));
  Double_t integral_48Ca_ppt=h_48Ca_ppt->Integral(h_48Ca_ppt->FindBin(18.0),h_48Ca_ppt->FindBin(34.0));

  Double_t integral_oxygen=integral_mylar_ppt-scale_mylar_carbon*integral_carbon_ppt;
  std::cout << "****  ppt integral raw ****" << std::endl;
  std::cout << "Mylar: " <<integral_mylar_ppt << std::endl;
  std::cout << "natC: " << integral_carbon_ppt << std::endl;
  std::cout << "40Ca: " << integral_40Ca_ppt << std::endl;
  std::cout << "42Ca: " << integral_42Ca_ppt << std::endl;
  std::cout << "44Ca: " << integral_44Ca_ppt << std::endl;
  std::cout << "48Ca: " << integral_48Ca_ppt << std::endl;

  std::cout << "****  ppt integral****" << std::endl;
  std::cout << "16O: " << integral_oxygen << std::endl;
  std::cout << "40Ca: " << integral_40Ca_ppt-scale_oxygen_40Ca*integral_oxygen << std::endl;
  std::cout << "42Ca: " << integral_42Ca_ppt-scale_oxygen_42Ca*integral_oxygen << std::endl;
  std::cout << "44Ca: " << integral_44Ca_ppt-scale_oxygen_44Ca*integral_oxygen << std::endl;
  std::cout << "48Ca: " << integral_48Ca_ppt-scale_oxygen_48Ca*integral_oxygen << std::endl;
  
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

  Double_t integral_mylar_pph=h_mylar_pph->Integral(h_mylar_pph->FindBin(15.0),h_mylar_pph->FindBin(34.0));
  Double_t integral_carbon_pph=h_carbon_pph->Integral(h_carbon_pph->FindBin(15.0),h_carbon_pph->FindBin(34.0));
  Double_t integral_40Ca_pph=h_40Ca_pph->Integral(h_40Ca_pph->FindBin(15.0),h_40Ca_pph->FindBin(34.0));
  Double_t integral_42Ca_pph=h_42Ca_pph->Integral(h_42Ca_pph->FindBin(15.0),h_42Ca_pph->FindBin(34.0));
  Double_t integral_44Ca_pph=h_44Ca_pph->Integral(h_44Ca_pph->FindBin(15.0),h_44Ca_pph->FindBin(34.0));

  Double_t integral_48Ca_mylar_pph=h_48Ca_mylar_pph->Integral(h_48Ca_mylar_pph->FindBin(28.0),h_48Ca_mylar_pph->FindBin(45.0));
  Double_t integral_48Ca_carbon_pph=h_48Ca_carbon_pph->Integral(h_48Ca_carbon_pph->FindBin(28.0),h_48Ca_carbon_pph->FindBin(45.0));
  Double_t integral_48Ca_pph=h_48Ca_pph->Integral(h_48Ca_pph->FindBin(28.0),h_48Ca_pph->FindBin(45.0));

  Double_t integral_oxygen_pph=integral_mylar_pph-scale_mylar_carbon*integral_carbon_pph;
  Double_t integral_48Ca_oxygen=integral_48Ca_mylar_pph-scale_mylar_carbon*integral_48Ca_carbon_pph;  

  std::cout << "****  pph integral raw ****" << std::endl;
  std::cout << "Mylar: " <<integral_mylar_pph << std::endl;
  std::cout << "natC: " << integral_carbon_pph << std::endl;
  std::cout << "40Ca: " << integral_40Ca_pph << std::endl;
  std::cout << "42Ca: " << integral_42Ca_pph << std::endl;
  std::cout << "44Ca: " << integral_44Ca_pph << std::endl;

  std::cout << "Mylar(48Ca): " << integral_48Ca_mylar_pph << std::endl;
  std::cout << "natC(48Ca): " << integral_48Ca_carbon_pph << std::endl;
  std::cout << "48Ca: " << integral_48Ca_pph << std::endl;

  std::cout << "****  pph integral****" << std::endl;
  std::cout << "16O: " << integral_oxygen_pph << std::endl;
  std::cout << "40Ca: " << integral_40Ca_pph-scale_oxygen_40Ca*integral_oxygen_pph << std::endl;
  std::cout << "42Ca: " << integral_42Ca_pph-scale_oxygen_42Ca*integral_oxygen_pph << std::endl;
  std::cout << "44Ca: " << integral_44Ca_pph-scale_oxygen_44Ca*integral_oxygen_pph << std::endl;
  std::cout << "48Ca: " << integral_48Ca_pph-scale_oxygen_48Ca*integral_48Ca_oxygen << std::endl;  

}

  
