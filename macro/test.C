#include <yaml-cpp/yaml.h>

void test(void){
  std::string path_config="prm/spectrometer/gr/ppt.yaml";
  std::ifstream fin(path_config);    
  YAML::Node node  = YAML::Load(fin);    
  Double_t fMagneticField = node["magfield"].as<Double_t>();    
  Double_t fMass = node["mass"].as<Double_t>();
  Int_t fAtomicNumber = node["atomicnum"].as<Int_t>();
  Double_t fRho = node["rho"].as<Double_t>();

  Double_t dE_gr=sqrt(fMass*fMass+pow(0.3*(Double_t) fAtomicNumber*fMagneticField*fRho*1.02,2.0))-sqrt(fMass*fMass+pow(0.3*(Double_t) fAtomicNumber*fMagneticField*fRho*0.98,2.0));

  std::cout << dE_gr << std::endl;

  return;
}
  
