#include "TParticleDataSimulator.h"
#include "TVector3.h"
#include "constant.h"
#include <iostream>
#include <string>
#include <fstream>
#include <TClonesArray.h>
#include <TClass.h>
#include <TParticleData.h>
#include <yaml-cpp/yaml.h>

using art::TParticleDataSimulator;


ClassImp(TParticleDataSimulator)

TParticleDataSimulator::TParticleDataSimulator()
: fOutput(NULL)
{

  Register(fMass("Mass","mass of particle",0.0));
  
  RegisterInputCollection("InputCollectionKineticE",
			  "input collection kinetic energy",
			  fNameKineticEInput, "KineticE",
			  &fKineticEInput, art::TSimpleData::Class_Name()
			  art::TSimpleData::Class_Name());

  RegisterInputCollection("InputCollectionTheta",
			  "input collection theta",
			  fNameThetaInput, "Theta",
			  &fThetaInput, art::TSimpleData::Class_Name(),
			  art::TSimpleData::Class_Name());
  
  RegisterInputCollection("InputCollectionPhi",
			  "input collection phi",
			  fNamePhiInput,"Phi",
			  &fPhiInput, art::TSimpleData::Class_Name(),
			  art::TSimpleData::Class_Name());      

  RegisterOutputCollection("OutputCollection","output collection",
			   fNameOutput,"TParticleData",
			   &fOutput, TClonesArray::Class_Name(),
			   art::TParticleData::Class_Name());  

}


TParticleDataSimulator::~TParticleDataSimulator()
{
  delete fOutput;
}

namespace {
}


void TParticleDataSimulator::Init(TEventCollection*){  
  return;  
}

void TParticleDataSimulator::Process(){

  fOutput->Clear("C");
  Bool_t kProcessed = kFALSE;

  const Int_t nDataKineticE = (*fKineticEInput)->GetEntriesFast();
  const Int_t nDataTheta    = (*fThetaInput)->GetEntriesFast();
  const Int_t nDataPhi      = (*fPhiInput)->GetEntriesFast();  

  if(nDataKineticE>0 && nDataTheta >0 && nDataPhi>0){
    kProcessed = kTRUE;
  TParticleData *outData = NULL;
  outData = static_cast<TParticleData*>(fOutput->ConstructedAt(0));
  
  TSimpleData *const inKineticE = static_cast<TSimpleData*>((*fKineticEInput)->At(0));
  TSimpleData *const inTheta = static_cast<TSimpleData*>((*fThetaInput)->At(0));
  TSimpleData *const inPhi = static_cast<TSimpleData*>((*fPhiInput)->At(0));        
  
  outData->SetTKE(fKineticEInput->GetValue());
  outData->SetMass(fMass);
  outData->SetTheta(fThetaInput->GetValue());
  outData->SetPhi(fPhiInput->GetValue());
  
  }
  return;
}
