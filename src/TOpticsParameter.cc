
#include "TOpticsParameter.h"

#include <fstream>
#include <TROOT.h>
#include <TList.h>
#include <yaml-cpp/yaml.h>

using art::TOpticsParameter;

ClassImp(TOpticsParameter)

TOpticsParameter::TOpticsParameter()
: fNParameter(0), fOpticsMatrixElement(NULL), fOrderX(NULL), fOrderY(NULL), fOrderA(NULL), fOrderB(NULL)
{
}

TOpticsParameter::~TOpticsParameter()
{
  fNParameter=0;
  delete fOpticsMatrixElement;
  delete fOrderX;
  delete fOrderY;
  delete fOrderA;
  delete fOrderB;
}

Bool_t TOpticsParameter::LoadYAMLNode(const YAML::Node& node) {
  try {
    fOrderX.push_back(node["OrderX"].as<Double_t>());
    fOrderY.push_back(node["OrderY"].as<Double_t>());
    fOrderA.push_back(node["OrderA"].as<Double_t>());
    fOrderB.push_back(node["OrderB"].as<Double_t>());
    fOpticsMatrixElement.push_back(node["OpticsMatrixElement"].as<Double_t>());
    fNParameter++;
    
  }catch (YAML::Exception& e){
      Error("LoadYAMLNode","Error occurred!");
      fprintf(stderr,"%s\n",e.what());
      return kFALSE;
  }
  return kTRUE;
  
  
}
