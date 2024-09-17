#include "TSpectrometerProcessor.h"
#include "TVector3.h"

#include "constant.h"
#include <iostream>
#include <string>
#include <fstream>
#include <TClonesArray.h>
#include <TClass.h>
#include <TOpticsData.h>
#include <TParticleData.h>
#include <yaml-cpp/yaml.h>

using art::TSpectrometerProcessor;


ClassImp(TSpectrometerProcessor)

TSpectrometerProcessor::TSpectrometerProcessor()
: fOutput(NULL)
{

  RegisterProcessorParameter("Setting","path to the setting file",
			     fInputFileName,TString("path/to/file"));
  
  RegisterInputCollection("InputCollection",
			  "input collection",
			  fNameInput, "OpticsData",
			  &fInput, TClonesArray::Class_Name(),
			  art::TOpticsData::Class_Name());  

  RegisterOutputCollection("OutputCollection","output collection",
                            fNameOutput,"TParticleData",
			   &fOutput, TClonesArray::Class_Name(),
			   art::TParticleData::Class_Name());  

}


TSpectrometerProcessor::~TSpectrometerProcessor()
{
  delete fOutput;
}

namespace {
}


void TSpectrometerProcessor::Init(TEventCollection*){

  std::ifstream fin(fInputFileName.Data());
  if(!fin.is_open()) {
      SetStateError(TString::Format("Cannot open configuration file: %s",fInputFileName.Data()));
      return;
   }
  try {

    YAML::Node node  = YAML::Load(fin);
    
    //fAngle = node["angle"].as<Double_t>();
    fTheta = node["theta"].as<Double_t>();
    fPhi = node["phi"].as<Double_t>();    

    fMagneticField = node["magfield"].as<Double_t>();

    fMass = node["mass"].as<Double_t>();
    fAtomicNumber = node["atomicnum"].as<Int_t>();
    fMassNumber = node["massnum"].as<Int_t>();

    fRho = node["rho"].as<Double_t>();

  }catch (YAML::Exception& e) {
    SetStateError(TString::Format("Error Occurred while loading file\n%s\n",
				  e.what()));
    return;
   }

  
  return;
  
}

void TSpectrometerProcessor::Process(){

  fOutput->Clear("C");
  Bool_t kProcessed = kFALSE;
  const Int_t nData = (*fInput)->GetEntriesFast();

  
  
  
  if (nData < 1) {
    kProcessed = kFALSE;    
  }
  else {
    kProcessed = kTRUE;    
    for (Int_t iData = 0; iData != nData; ++iData) {
      
      TParticleData *outData = NULL;
      outData = static_cast<TParticleData*>(fOutput->ConstructedAt(iData));

      TOpticsData *const inData = static_cast<TOpticsData*>((*fInput)->At(iData));
      
      double Delta = inData->GetDelta();
      double A = inData->GetA();
      double B = inData->GetB();
      double Z = inData->GetZ();      

      double ThetaRad=fTheta*TMath::DegToRad();
      double PhiRad=fPhi*TMath::DegToRad();
      
      double rx=A*cos(ThetaRad)*cos(PhiRad)-B*sin(PhiRad)+sin(ThetaRad)*cos(PhiRad);
      double ry=A*cos(ThetaRad)*sin(PhiRad)+B*cos(PhiRad)+sin(ThetaRad)*sin(PhiRad);
      double rz=-A*sin(ThetaRad)+cos(ThetaRad);

      TVector3 r(rx,ry,rz);

      double c=0.299792458;
      
      double TKE = sqrt(fMass*fMass + pow(c*((double) fAtomicNumber)*fMagneticField*fRho*(1+Delta),2.0))-fMass;
      //double theta_lab = TMath::RadToDeg()*atan( sqrt( pow( tan( atan(A)+fAngle*TMath::DegToRad() ),2.0) + pow(B,2.0)) );
      //double phi_lab = TMath::RadToDeg()*atan(B/tan( atan(A)+fAngle));
      double theta_lab = TMath::RadToDeg()*r.Theta();
      double phi_lab = TMath::RadToDeg()*r.Phi();
      
      double TOF = (Z/c)*sqrt(1.0+pow(fMass/(c*fAtomicNumber*fMagneticField*fRho*(1+Delta)),2.0));
      double velocity = c/sqrt(1.0+pow(fMass/(c*fAtomicNumber*fMagneticField*fRho*(1+Delta)),2.0));      
      outData->SetTKE(TKE);
      outData->SetMass(fMass);
      outData->SetTheta(theta_lab);
      outData->SetPhi(phi_lab);
      outData->SetTOF(TOF);
      outData->SetVelocity(velocity);      


    }
  }
  
  return;
}
